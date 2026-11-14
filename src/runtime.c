/*
 * Handle objects, registries, value structs and checks. See runtime.h and the design spec.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_thorvg.h"
#include "zend_exceptions.h"
#include "ext/standard/html.h"
#include "runtime.h"
#include "../stubs/thorvg_types_arginfo.h"

ZEND_DECLARE_MODULE_GLOBALS(thorvg)

zend_class_entry *tvg_handle_ce[TVG_K_COUNT];
zend_class_entry *tvg_point_ce, *tvg_matrix_ce, *tvg_region_ce, *tvg_color_stop_ce, *tvg_text_metrics_ce,
	*tvg_glyph_metrics_ce, *tvg_wgcontext_ce, *tvg_audio_info_ce;

static zend_object_handlers tvg_handle_handlers;

static const char *tvg_kind_name[TVG_K_COUNT] = {
	"Tvg_Canvas", "Tvg_Paint", "Tvg_Gradient", "Tvg_Saver", "Tvg_Animation", "Tvg_Accessor", "Tvg_Video",
};

/* ---- handles ---- */

static zend_object *tvg_handle_create(zend_class_entry *ce)
{
	tvg_handle_obj *h = zend_object_alloc(sizeof(tvg_handle_obj), ce);

	h->ptr = NULL;
	h->kind = -1;
	h->owner = NULL;
	h->picture = NULL;
	h->user_refs = 0;
	ZVAL_UNDEF(&h->keep);
	zend_object_std_init(&h->std, ce);
	object_properties_init(&h->std, ce);
	h->std.handlers = &tvg_handle_handlers;
	return &h->std;
}

static void tvg_registry_drop(HashTable *table, void *ptr, zend_object *o)
{
	zval *entry;

	if (!TVG_G(live) || ptr == NULL) {
		return;
	}
	entry = zend_hash_index_find(table, (zend_ulong) (uintptr_t) ptr);
	if (entry != NULL && Z_PTR_P(entry) == o) {
		zend_hash_index_del(table, (zend_ulong) (uintptr_t) ptr);
	}
}

static void tvg_handle_free(zend_object *o)
{
	tvg_handle_obj *h = tvg_handle_from(o);

	switch (h->kind) {
		case TVG_K_CANVAS:
			if (h->ptr != NULL) {
				/* A draw may still be writing into the target: finish it before the canvas goes. */
				tvg_canvas_sync((Tvg_Canvas) h->ptr);
				tvg_canvas_destroy((Tvg_Canvas) h->ptr);
			}
			break;
		case TVG_K_PAINT:
			if (h->ptr != NULL) {
				tvg_registry_drop(&TVG_G(paints), h->ptr, o);
				tvg_paint_unref((Tvg_Paint) h->ptr, true);
			}
			break;
		case TVG_K_GRADIENT:
			if (h->ptr != NULL) {
				tvg_registry_drop(&TVG_G(gradients), h->ptr, o);
				if (h->owner == NULL) {
					tvg_gradient_del((Tvg_Gradient) h->ptr);
				}
			}
			if (h->owner != NULL) {
				tvg_paint_unref(h->owner, true);
			}
			break;
		case TVG_K_SAVER:
			if (h->ptr != NULL) {
				/* The GIF saver renders on a worker thread until sync. */
				tvg_saver_sync((Tvg_Saver) h->ptr);
				tvg_saver_del((Tvg_Saver) h->ptr);
			}
			break;
		case TVG_K_ANIMATION:
			if (h->ptr != NULL) {
				if (h->picture != NULL) {
					tvg_paint_unref(h->picture, false);
				}
				tvg_animation_del((Tvg_Animation) h->ptr);
			}
			break;
		case TVG_K_ACCESSOR:
			if (h->ptr != NULL) {
				tvg_accessor_del((Tvg_Accessor) h->ptr);
			}
			break;
		case TVG_K_VIDEO:
			if (h->ptr != NULL) {
				tvg_video_del((Tvg_Video) h->ptr);
			}
			break;
	}
	h->ptr = NULL;
	zval_ptr_dtor(&h->keep);
	ZVAL_UNDEF(&h->keep);
	zend_object_std_dtor(o);
}

static HashTable *tvg_handle_gc(zend_object *o, zval **table, int *n)
{
	tvg_handle_obj *h = tvg_handle_from(o);

	if (Z_TYPE(h->keep) != IS_UNDEF) {
		*table = &h->keep;
		*n = 1;
	} else {
		*table = NULL;
		*n = 0;
	}
	return zend_std_get_properties(o);
}

void tvg_handle_new(int kind, void *ptr, zval *out)
{
	tvg_handle_obj *h;

	if (ptr == NULL) {
		ZVAL_NULL(out);
		return;
	}
	object_init_ex(out, tvg_handle_ce[kind]);
	h = tvg_handle_from(Z_OBJ_P(out));
	h->kind = kind;
	h->ptr = ptr;
	if (kind == TVG_K_ANIMATION) {
		/* ThorVG's saver deletes an animation whose picture only it references: hold one more. */
		h->picture = tvg_animation_get_picture((Tvg_Animation) ptr);
		if (h->picture != NULL) {
			tvg_paint_ref(h->picture);
		}
	}
}

void tvg_handle_release(zend_object *o)
{
	tvg_handle_obj *h = tvg_handle_from(o);

	if (h->kind == TVG_K_PAINT) {
		tvg_registry_drop(&TVG_G(paints), h->ptr, o);
	} else if (h->kind == TVG_K_GRADIENT) {
		tvg_registry_drop(&TVG_G(gradients), h->ptr, o);
		if (h->owner != NULL) {
			tvg_paint_unref(h->owner, true);
			h->owner = NULL;
		}
	}
	h->ptr = NULL;
}

void *tvg_handle_arg(zval *zv, int kind, uint32_t arg_num)
{
	tvg_handle_obj *h = tvg_handle_from(Z_OBJ_P(zv));

	if (h->ptr == NULL) {
		zend_argument_value_error(arg_num, "is a released %s", tvg_kind_name[kind]);
		return NULL;
	}
	return h->ptr;
}

/* ---- paints ---- */

void tvg_paint_wrap(Tvg_Paint paint, zval *out)
{
	zval *found;

	if (paint == NULL) {
		ZVAL_NULL(out);
		return;
	}
	found = zend_hash_index_find(&TVG_G(paints), (zend_ulong) (uintptr_t) paint);
	if (found != NULL) {
		zend_object *o = Z_PTR_P(found);
		GC_ADDREF(o);
		ZVAL_OBJ(out, o);
		return;
	}
	tvg_handle_new(TVG_K_PAINT, paint, out);
	tvg_paint_ref(paint);
	zend_hash_index_add_new_ptr(&TVG_G(paints), (zend_ulong) (uintptr_t) paint, Z_OBJ_P(out));
}

static const char *tvg_type_name(Tvg_Type type)
{
	switch (type) {
		case TVG_TYPE_SHAPE: return "a shape";
		case TVG_TYPE_SCENE: return "a scene";
		case TVG_TYPE_PICTURE: return "a picture";
		case TVG_TYPE_TEXT: return "a text";
		default: return "a paint";
	}
}

Tvg_Paint tvg_paint_arg(zval *zv, Tvg_Type type, uint32_t arg_num)
{
	Tvg_Paint paint = tvg_handle_arg(zv, TVG_K_PAINT, arg_num);
	Tvg_Type actual = TVG_TYPE_UNDEF;

	if (paint == NULL || type == TVG_TYPE_UNDEF) {
		return paint;
	}
	tvg_paint_get_type(paint, &actual);
	if (actual != type) {
		zend_argument_type_error(arg_num, "must be %s, %s given", tvg_type_name(type), tvg_type_name(actual));
		return NULL;
	}
	return paint;
}

/* ---- gradients ---- */

void tvg_gradient_wrap(Tvg_Gradient gradient, Tvg_Paint owner, zval *out)
{
	zval *found;
	tvg_handle_obj *h;

	if (gradient == NULL) {
		ZVAL_NULL(out);
		return;
	}
	found = zend_hash_index_find(&TVG_G(gradients), (zend_ulong) (uintptr_t) gradient);
	if (found != NULL) {
		zend_object *o = Z_PTR_P(found);
		GC_ADDREF(o);
		ZVAL_OBJ(out, o);
		return;
	}
	tvg_handle_new(TVG_K_GRADIENT, gradient, out);
	h = tvg_handle_from(Z_OBJ_P(out));
	if (owner != NULL) {
		h->owner = owner;
		tvg_paint_ref(owner);
	}
	zend_hash_index_add_new_ptr(&TVG_G(gradients), (zend_ulong) (uintptr_t) gradient, Z_OBJ_P(out));
}

Tvg_Gradient tvg_gradient_arg(zval *zv, uint32_t arg_num)
{
	tvg_handle_obj *h = tvg_handle_from(Z_OBJ_P(zv));
	Tvg_Gradient fill = NULL, stroke = NULL;

	if (h->ptr == NULL) {
		zend_argument_value_error(arg_num, "is a released Tvg_Gradient (set on a paint, deleted, or replaced)");
		return NULL;
	}
	if (h->owner != NULL) {
		tvg_shape_get_gradient(h->owner, &fill);
		tvg_shape_get_stroke_gradient(h->owner, &stroke);
		if (h->ptr != fill && h->ptr != stroke) {
			tvg_handle_release(&h->std);
			zend_argument_value_error(arg_num, "is a Tvg_Gradient its shape no longer holds");
			return NULL;
		}
	}
	return (Tvg_Gradient) h->ptr;
}

bool tvg_gradient_can_attach(zval *gradient_zv, uint32_t arg_num)
{
	if (tvg_gradient_arg(gradient_zv, arg_num) == NULL) {
		return false;
	}
	if (tvg_handle_from(Z_OBJ_P(gradient_zv))->owner != NULL) {
		zend_argument_value_error(arg_num, "belongs to a shape; set a tvg_gradient_duplicate() of it");
		return false;
	}
	return true;
}

void tvg_gradient_attached(zval *gradient_zv)
{
	tvg_handle_release(Z_OBJ_P(gradient_zv));
}

/* ---- callbacks ---- */

static void tvg_callback_dtor(zval *zv)
{
	tvg_callback *cb = Z_PTR_P(zv);

	zval_ptr_dtor(&cb->callable);
	zval_ptr_dtor(&cb->data);
	efree(cb);
}

tvg_callback *tvg_callback_new(zval *callable, zval *data)
{
	tvg_callback *cb = emalloc(sizeof(tvg_callback));

	ZVAL_COPY(&cb->callable, callable);
	ZVAL_COPY(&cb->data, data);
	cb->thread = pthread_self();
	zend_hash_next_index_insert_ptr(&TVG_G(callbacks), cb);
	return cb;
}

bool tvg_callback_call(tvg_callback *cb, zval *args, uint32_t argc, zval *retval)
{
	ZVAL_UNDEF(retval);
	if (cb == NULL || Z_TYPE(cb->callable) == IS_UNDEF || !pthread_equal(cb->thread, pthread_self()) || EG(exception)) {
		return false;
	}
	if (call_user_function(NULL, NULL, &cb->callable, retval, argc, args) != SUCCESS || EG(exception)) {
		zval_ptr_dtor(retval);
		ZVAL_UNDEF(retval);
		return false;
	}
	return true;
}

/* ---- borrowed bytes ---- */

void tvg_borrow(zend_string *s)
{
	zend_hash_next_index_insert_ptr(&TVG_G(borrowed), zend_string_copy(s));
}

void tvg_borrow_font(const char *name)
{
	zend_hash_str_update_ptr(&TVG_G(fonts), name, strlen(name), NULL);
}

bool tvg_memory_arg(zend_string *str, zend_long address, size_t need, uint32_t arg_num, const void **bytes)
{
	if (str != NULL) {
		if (ZSTR_LEN(str) < need) {
			zend_argument_value_error(arg_num, "must hold %zu bytes, %zu given", need, ZSTR_LEN(str));
			return false;
		}
		*bytes = ZSTR_VAL(str);
		return true;
	}
	/* An address, trusted to hold `need` bytes; 0 is NULL, which ThorVG refuses itself. */
	*bytes = (const void *) (uintptr_t) address;
	return true;
}

/* ---- value structs ---- */

static double tvg_prop_double(zend_object *o, int slot)
{
	return zval_get_double(OBJ_PROP_NUM(o, slot));
}

static zend_long tvg_prop_long(zend_object *o, int slot)
{
	return zval_get_long(OBJ_PROP_NUM(o, slot));
}

static void tvg_prop_set_double(zend_object *o, int slot, double v)
{
	zval *p = OBJ_PROP_NUM(o, slot);
	zval_ptr_dtor(p);
	ZVAL_DOUBLE(p, v);
}

static void tvg_prop_set_long(zend_object *o, int slot, zend_long v)
{
	zval *p = OBJ_PROP_NUM(o, slot);
	zval_ptr_dtor(p);
	ZVAL_LONG(p, v);
}

void tvg_point_read(zend_object *o, Tvg_Point *out)
{
	out->x = (float) tvg_prop_double(o, 0);
	out->y = (float) tvg_prop_double(o, 1);
}

void tvg_point_write(zend_object *o, const Tvg_Point *in)
{
	tvg_prop_set_double(o, 0, in->x);
	tvg_prop_set_double(o, 1, in->y);
}

void tvg_point_new(const Tvg_Point *in, zval *out)
{
	object_init_ex(out, tvg_point_ce);
	tvg_point_write(Z_OBJ_P(out), in);
}

void tvg_matrix_read(zend_object *o, Tvg_Matrix *out)
{
	out->e11 = (float) tvg_prop_double(o, 0);
	out->e12 = (float) tvg_prop_double(o, 1);
	out->e13 = (float) tvg_prop_double(o, 2);
	out->e21 = (float) tvg_prop_double(o, 3);
	out->e22 = (float) tvg_prop_double(o, 4);
	out->e23 = (float) tvg_prop_double(o, 5);
	out->e31 = (float) tvg_prop_double(o, 6);
	out->e32 = (float) tvg_prop_double(o, 7);
	out->e33 = (float) tvg_prop_double(o, 8);
}

void tvg_matrix_write(zend_object *o, const Tvg_Matrix *in)
{
	tvg_prop_set_double(o, 0, in->e11);
	tvg_prop_set_double(o, 1, in->e12);
	tvg_prop_set_double(o, 2, in->e13);
	tvg_prop_set_double(o, 3, in->e21);
	tvg_prop_set_double(o, 4, in->e22);
	tvg_prop_set_double(o, 5, in->e23);
	tvg_prop_set_double(o, 6, in->e31);
	tvg_prop_set_double(o, 7, in->e32);
	tvg_prop_set_double(o, 8, in->e33);
}

void tvg_region_new(const Tvg_Region *in, zval *out)
{
	object_init_ex(out, tvg_region_ce);
	tvg_prop_set_long(Z_OBJ_P(out), 0, in->xMin);
	tvg_prop_set_long(Z_OBJ_P(out), 1, in->yMin);
	tvg_prop_set_long(Z_OBJ_P(out), 2, in->xMax);
	tvg_prop_set_long(Z_OBJ_P(out), 3, in->yMax);
}

bool tvg_color_stop_read(zend_object *o, Tvg_Color_Stop *out, uint32_t arg_num)
{
	zend_long c[4];
	int i;

	for (i = 0; i < 4; i++) {
		c[i] = tvg_prop_long(o, i + 1);
		if (c[i] < 0 || c[i] > 255) {
			zend_argument_value_error(arg_num, "must hold Tvg_Color_Stop channels between 0 and 255");
			return false;
		}
	}
	out->offset = (float) tvg_prop_double(o, 0);
	out->r = (uint8_t) c[0];
	out->g = (uint8_t) c[1];
	out->b = (uint8_t) c[2];
	out->a = (uint8_t) c[3];
	return true;
}

void tvg_color_stop_new(const Tvg_Color_Stop *in, zval *out)
{
	object_init_ex(out, tvg_color_stop_ce);
	tvg_prop_set_double(Z_OBJ_P(out), 0, in->offset);
	tvg_prop_set_long(Z_OBJ_P(out), 1, in->r);
	tvg_prop_set_long(Z_OBJ_P(out), 2, in->g);
	tvg_prop_set_long(Z_OBJ_P(out), 3, in->b);
	tvg_prop_set_long(Z_OBJ_P(out), 4, in->a);
}

void tvg_text_metrics_write(zend_object *o, const Tvg_Text_Metrics *in)
{
	tvg_prop_set_double(o, 0, in->ascent);
	tvg_prop_set_double(o, 1, in->descent);
	tvg_prop_set_double(o, 2, in->linegap);
	tvg_prop_set_double(o, 3, in->advance);
}

void tvg_glyph_metrics_write(zend_object *o, const Tvg_Glyph_Metrics *in)
{
	zval min, max;

	tvg_prop_set_double(o, 0, in->advance);
	tvg_prop_set_double(o, 1, in->bearing);
	tvg_point_new(&in->min, &min);
	tvg_point_new(&in->max, &max);
	zval_ptr_dtor(OBJ_PROP_NUM(o, 2));
	ZVAL_COPY_VALUE(OBJ_PROP_NUM(o, 2), &min);
	zval_ptr_dtor(OBJ_PROP_NUM(o, 3));
	ZVAL_COPY_VALUE(OBJ_PROP_NUM(o, 3), &max);
}

void tvg_wgcontext_read(zend_object *o, Tvg_WgContext *out)
{
	out->instance = (void *) (uintptr_t) tvg_prop_long(o, 0);
	out->adapter = (void *) (uintptr_t) tvg_prop_long(o, 1);
	out->device = (void *) (uintptr_t) tvg_prop_long(o, 2);
}

/* ---- lists ---- */

bool tvg_list_count(HashTable *list, zend_long count, uint32_t arg_num)
{
	if (count < 0 || (list == NULL && count > 0) || (list != NULL && (zend_ulong) count > zend_hash_num_elements(list))) {
		zend_argument_value_error(arg_num, "is a count of " ZEND_LONG_FMT " for a list of %u", count, list != NULL ? zend_hash_num_elements(list) : 0);
		return false;
	}
	if ((zend_ulong) count > UINT32_MAX) {
		zend_argument_value_error(arg_num, "must be at most 4294967295");
		return false;
	}
	return true;
}

Tvg_Point *tvg_points_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok)
{
	Tvg_Point *out;
	zval *el;
	zend_long i = 0;

	*ok = false;
	if (count == 0) {
		*ok = true;
		return NULL;
	}
	out = safe_emalloc((size_t) count, sizeof(Tvg_Point), 0);
	ZEND_HASH_FOREACH_VAL(list, el) {
		if (i == count) {
			break;
		}
		ZVAL_DEREF(el);
		if (Z_TYPE_P(el) != IS_OBJECT || Z_OBJCE_P(el) != tvg_point_ce) {
			zend_argument_type_error(arg_num, "must be a list of Tvg_Point, element " ZEND_LONG_FMT " is %s", i, zend_zval_value_name(el));
			efree(out);
			return NULL;
		}
		tvg_point_read(Z_OBJ_P(el), &out[i]);
		if (!zend_finite(out[i].x) || !zend_finite(out[i].y)) {
			zend_argument_value_error(arg_num, "must hold finite points, element " ZEND_LONG_FMT " is not", i);
			efree(out);
			return NULL;
		}
		i++;
	} ZEND_HASH_FOREACH_END();
	*ok = true;
	return out;
}

Tvg_Path_Command *tvg_commands_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok)
{
	Tvg_Path_Command *out;
	zval *el;
	zend_long i = 0;

	*ok = false;
	if (count == 0) {
		*ok = true;
		return NULL;
	}
	out = safe_emalloc((size_t) count, sizeof(Tvg_Path_Command), 0);
	ZEND_HASH_FOREACH_VAL(list, el) {
		if (i == count) {
			break;
		}
		ZVAL_DEREF(el);
		if (Z_TYPE_P(el) != IS_LONG || Z_LVAL_P(el) < TVG_PATH_COMMAND_CLOSE || Z_LVAL_P(el) > TVG_PATH_COMMAND_CUBIC_TO) {
			zend_argument_value_error(arg_num, "must be a list of TVG_PATH_COMMAND_* values, element " ZEND_LONG_FMT " is not", i);
			efree(out);
			return NULL;
		}
		out[i++] = (Tvg_Path_Command) Z_LVAL_P(el);
	} ZEND_HASH_FOREACH_END();
	*ok = true;
	return out;
}

float *tvg_floats_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok)
{
	float *out;
	zval *el;
	zend_long i = 0;

	*ok = false;
	if (count == 0) {
		*ok = true;
		return NULL;
	}
	out = safe_emalloc((size_t) count, sizeof(float), 0);
	ZEND_HASH_FOREACH_VAL(list, el) {
		if (i == count) {
			break;
		}
		ZVAL_DEREF(el);
		if (Z_TYPE_P(el) != IS_LONG && Z_TYPE_P(el) != IS_DOUBLE) {
			zend_argument_type_error(arg_num, "must be a list of floats, element " ZEND_LONG_FMT " is %s", i, zend_zval_value_name(el));
			efree(out);
			return NULL;
		}
		out[i++] = (float) zval_get_double(el);
	} ZEND_HASH_FOREACH_END();
	*ok = true;
	return out;
}

Tvg_Color_Stop *tvg_stops_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok)
{
	Tvg_Color_Stop *out;
	zval *el;
	zend_long i = 0;

	*ok = false;
	if (count == 0) {
		*ok = true;
		return NULL;
	}
	out = safe_emalloc((size_t) count, sizeof(Tvg_Color_Stop), 0);
	ZEND_HASH_FOREACH_VAL(list, el) {
		if (i == count) {
			break;
		}
		ZVAL_DEREF(el);
		if (Z_TYPE_P(el) != IS_OBJECT || Z_OBJCE_P(el) != tvg_color_stop_ce) {
			zend_argument_type_error(arg_num, "must be a list of Tvg_Color_Stop, element " ZEND_LONG_FMT " is %s", i, zend_zval_value_name(el));
			efree(out);
			return NULL;
		}
		if (!tvg_color_stop_read(Z_OBJ_P(el), &out[i++], arg_num)) {
			efree(out);
			return NULL;
		}
	} ZEND_HASH_FOREACH_END();
	*ok = true;
	return out;
}

/* ---- checks ---- */

bool tvg_range(zend_long value, zend_long min, zend_long max, const char *what, uint32_t arg_num)
{
	if (value < min || value > max) {
		zend_argument_value_error(arg_num, "must be %s", what);
		return false;
	}
	return true;
}

bool tvg_finite_args(const double *values, int count, uint32_t first_arg)
{
	int i;

	for (i = 0; i < count; i++) {
		if (!zend_finite(values[i])) {
			zend_argument_value_error(first_arg + (uint32_t) i, "must be finite");
			return false;
		}
	}
	return true;
}

bool tvg_path_utf8(const char *path, size_t len, uint32_t arg_num)
{
	size_t cursor = 0;
	zend_result status = SUCCESS;

	while (cursor < len) {
		php_next_utf8_char((const unsigned char *) path, len, &cursor, &status);
		if (status != SUCCESS) {
			zend_argument_value_error(arg_num, "must be valid UTF-8");
			return false;
		}
	}
	return true;
}

bool tvg_path_allowed(const char *path)
{
	return php_check_open_basedir(path) == 0;
}

/* ---- struct constructors and private handle constructors ---- */

ZEND_METHOD(Tvg_Canvas, __construct) {}
ZEND_METHOD(Tvg_Paint, __construct) {}
ZEND_METHOD(Tvg_Gradient, __construct) {}
ZEND_METHOD(Tvg_Saver, __construct) {}
ZEND_METHOD(Tvg_Animation, __construct) {}
ZEND_METHOD(Tvg_Accessor, __construct) {}
ZEND_METHOD(Tvg_Video, __construct) {}

ZEND_METHOD(Tvg_Point, __construct)
{
	double x = 0.0, y = 0.0;

	ZEND_PARSE_PARAMETERS_START(0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), 0, x);
	tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), 1, y);
}

ZEND_METHOD(Tvg_Matrix, __construct)
{
	double e[9] = {0};
	int i;

	ZEND_PARSE_PARAMETERS_START(0, 9)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(e[0])
		Z_PARAM_DOUBLE(e[1])
		Z_PARAM_DOUBLE(e[2])
		Z_PARAM_DOUBLE(e[3])
		Z_PARAM_DOUBLE(e[4])
		Z_PARAM_DOUBLE(e[5])
		Z_PARAM_DOUBLE(e[6])
		Z_PARAM_DOUBLE(e[7])
		Z_PARAM_DOUBLE(e[8])
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 9; i++) {
		tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), i, e[i]);
	}
}

ZEND_METHOD(Tvg_Region, __construct)
{
	zend_long v[4] = {0};
	int i;

	ZEND_PARSE_PARAMETERS_START(0, 4)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(v[0])
		Z_PARAM_LONG(v[1])
		Z_PARAM_LONG(v[2])
		Z_PARAM_LONG(v[3])
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 4; i++) {
		tvg_prop_set_long(Z_OBJ_P(ZEND_THIS), i, v[i]);
	}
}

ZEND_METHOD(Tvg_Color_Stop, __construct)
{
	double offset = 0.0;
	zend_long c[4] = {0};
	int i;

	ZEND_PARSE_PARAMETERS_START(0, 5)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(offset)
		Z_PARAM_LONG(c[0])
		Z_PARAM_LONG(c[1])
		Z_PARAM_LONG(c[2])
		Z_PARAM_LONG(c[3])
	ZEND_PARSE_PARAMETERS_END();

	tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), 0, offset);
	for (i = 0; i < 4; i++) {
		tvg_prop_set_long(Z_OBJ_P(ZEND_THIS), i + 1, c[i]);
	}
}

ZEND_METHOD(Tvg_Text_Metrics, __construct)
{
	double v[4] = {0};
	int i;

	ZEND_PARSE_PARAMETERS_START(0, 4)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(v[0])
		Z_PARAM_DOUBLE(v[1])
		Z_PARAM_DOUBLE(v[2])
		Z_PARAM_DOUBLE(v[3])
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 4; i++) {
		tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), i, v[i]);
	}
}

ZEND_METHOD(Tvg_Glyph_Metrics, __construct)
{
	double advance = 0.0, bearing = 0.0;
	zend_object *min = NULL, *max = NULL;
	zval point;
	Tvg_Point zero = {0.0f, 0.0f};

	ZEND_PARSE_PARAMETERS_START(0, 4)
		Z_PARAM_OPTIONAL
		Z_PARAM_DOUBLE(advance)
		Z_PARAM_DOUBLE(bearing)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(min, tvg_point_ce)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(max, tvg_point_ce)
	ZEND_PARSE_PARAMETERS_END();

	tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), 0, advance);
	tvg_prop_set_double(Z_OBJ_P(ZEND_THIS), 1, bearing);
	if (min != NULL) {
		GC_ADDREF(min);
		ZVAL_OBJ(&point, min);
	} else {
		tvg_point_new(&zero, &point);
	}
	zval_ptr_dtor(OBJ_PROP_NUM(Z_OBJ_P(ZEND_THIS), 2));
	ZVAL_COPY_VALUE(OBJ_PROP_NUM(Z_OBJ_P(ZEND_THIS), 2), &point);
	if (max != NULL) {
		GC_ADDREF(max);
		ZVAL_OBJ(&point, max);
	} else {
		tvg_point_new(&zero, &point);
	}
	zval_ptr_dtor(OBJ_PROP_NUM(Z_OBJ_P(ZEND_THIS), 3));
	ZVAL_COPY_VALUE(OBJ_PROP_NUM(Z_OBJ_P(ZEND_THIS), 3), &point);
}

ZEND_METHOD(Tvg_WgContext, __construct)
{
	zend_long v[3] = {0};
	int i;

	ZEND_PARSE_PARAMETERS_START(0, 3)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(v[0])
		Z_PARAM_LONG(v[1])
		Z_PARAM_LONG(v[2])
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 3; i++) {
		tvg_prop_set_long(Z_OBJ_P(ZEND_THIS), i, v[i]);
	}
}

ZEND_METHOD(Tvg_Audio_Info, __construct)
{
	ZEND_PARSE_PARAMETERS_NONE();
}

/* ---- lifecycle ---- */

void tvg_runtime_minit(int module_number)
{
	int i;

	memcpy(&tvg_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	tvg_handle_handlers.offset = XtOffsetOf(tvg_handle_obj, std);
	tvg_handle_handlers.free_obj = tvg_handle_free;
	tvg_handle_handlers.clone_obj = NULL;
	tvg_handle_handlers.get_gc = tvg_handle_gc;

	tvg_handle_ce[TVG_K_CANVAS] = register_class_Tvg_Canvas();
	tvg_handle_ce[TVG_K_PAINT] = register_class_Tvg_Paint();
	tvg_handle_ce[TVG_K_GRADIENT] = register_class_Tvg_Gradient();
	tvg_handle_ce[TVG_K_SAVER] = register_class_Tvg_Saver();
	tvg_handle_ce[TVG_K_ANIMATION] = register_class_Tvg_Animation();
	tvg_handle_ce[TVG_K_ACCESSOR] = register_class_Tvg_Accessor();
	tvg_handle_ce[TVG_K_VIDEO] = register_class_Tvg_Video();
	for (i = 0; i < TVG_K_COUNT; i++) {
		tvg_handle_ce[i]->create_object = tvg_handle_create;
	}

	tvg_point_ce = register_class_Tvg_Point();
	tvg_matrix_ce = register_class_Tvg_Matrix();
	tvg_region_ce = register_class_Tvg_Region();
	tvg_color_stop_ce = register_class_Tvg_Color_Stop();
	tvg_text_metrics_ce = register_class_Tvg_Text_Metrics();
	tvg_glyph_metrics_ce = register_class_Tvg_Glyph_Metrics();
	tvg_wgcontext_ce = register_class_Tvg_WgContext();
	tvg_audio_info_ce = register_class_Tvg_Audio_Info();
}

static void tvg_borrowed_dtor(zval *zv)
{
	zend_string_release((zend_string *) Z_PTR_P(zv));
}

void tvg_runtime_rinit(void)
{
	zend_hash_init(&TVG_G(paints), 16, NULL, NULL, 0);
	zend_hash_init(&TVG_G(gradients), 8, NULL, NULL, 0);
	zend_hash_init(&TVG_G(borrowed), 4, NULL, tvg_borrowed_dtor, 0);
	zend_hash_init(&TVG_G(fonts), 4, NULL, NULL, 0);
	zend_hash_init(&TVG_G(callbacks), 4, NULL, tvg_callback_dtor, 0);
	TVG_G(live) = true;
}

/* Before the object store is freed: callables and their data may be objects. Records stay until post-deactivate. */
void tvg_runtime_rshutdown(void)
{
	tvg_callback *cb;

	ZEND_HASH_FOREACH_PTR(&TVG_G(callbacks), cb) {
		zval_ptr_dtor(&cb->callable);
		ZVAL_UNDEF(&cb->callable);
		zval_ptr_dtor(&cb->data);
		ZVAL_UNDEF(&cb->data);
	} ZEND_HASH_FOREACH_END();
}

/* After the object store is freed: nothing of this request still reads borrowed bytes but the font table. */
void tvg_runtime_post_deactivate(void)
{
	zend_string *name;

	if (!TVG_G(live)) {
		return;
	}
	ZEND_HASH_FOREACH_STR_KEY(&TVG_G(fonts), name) {
		if (name != NULL) {
			tvg_font_unload(ZSTR_VAL(name));
		}
	} ZEND_HASH_FOREACH_END();
	TVG_G(live) = false;
	zend_hash_destroy(&TVG_G(fonts));
	zend_hash_destroy(&TVG_G(callbacks));
	zend_hash_destroy(&TVG_G(borrowed));
	zend_hash_destroy(&TVG_G(gradients));
	zend_hash_destroy(&TVG_G(paints));
}
