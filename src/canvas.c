/*
 * Engine and canvas bindings (thorvg_canvas.stub.php).
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_canvas_arginfo.h"

/* A Tvg_Colorspace value: 0..6 or TVG_COLORSPACE_UNKNOWN. */
static bool tvg_colorspace_arg(zend_long cs, uint32_t arg_num)
{
	if ((cs >= TVG_COLORSPACE_ABGR8888 && cs <= TVG_COLORSPACE_XRGB8888) || cs == TVG_COLORSPACE_UNKNOWN) {
		return true;
	}
	zend_argument_value_error(arg_num, "must be a TVG_COLORSPACE_* value");
	return false;
}

static Tvg_Canvas tvg_canvas_arg(zval *zv, uint32_t arg_num)
{
	return (Tvg_Canvas) tvg_handle_arg(zv, TVG_K_CANVAS, arg_num);
}

ZEND_FUNCTION(tvg_engine_init)
{
	zend_long threads;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(threads)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(threads, 0, UINT_MAX, "between 0 and 4294967295", 1)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_engine_init((unsigned) threads));
}

ZEND_FUNCTION(tvg_engine_term)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG((zend_long) tvg_engine_term());
}

ZEND_FUNCTION(tvg_swcanvas_create)
{
	zend_long op;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(op)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(op, 0, TVG_ENGINE_OPTION_DEFAULT | TVG_ENGINE_OPTION_SMART_RENDER | TVG_ENGINE_OPTION_ALIASED, "a combination of TVG_ENGINE_OPTION_* flags", 1)) {
		RETURN_THROWS();
	}
	tvg_handle_new(TVG_K_CANVAS, tvg_swcanvas_create((Tvg_Engine_Option) op), return_value);
}

ZEND_FUNCTION(tvg_swcanvas_set_target)
{
	zval *canvas_zv;
	zend_string *buffer = NULL;
	zend_long address = 0, stride, w, h, cs;
	Tvg_Canvas canvas;
	const void *bytes;
	Tvg_Result result;
	tvg_handle_obj *handle;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_STR_OR_LONG(buffer, address)
		Z_PARAM_LONG(stride)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(stride, 3) || !tvg_u32(w, 4) || !tvg_u32(h, 5) || !tvg_colorspace_arg(cs, 6)) {
		RETURN_THROWS();
	}
	if (buffer != NULL && ZSTR_IS_INTERNED(buffer)) {
		/* ThorVG writes into the buffer: an interned string is shared by every use of that literal. */
		zend_argument_value_error(2, "must not be an interned string (a literal); build it at run time, e.g. with str_repeat()");
		RETURN_THROWS();
	}
	if (!tvg_memory_arg(buffer, address, (size_t) stride * (size_t) h * 4, 2, &bytes)) {
		RETURN_THROWS();
	}
	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}

	result = tvg_swcanvas_set_target(canvas, (uint32_t *) bytes, (uint32_t) stride, (uint32_t) w, (uint32_t) h, (Tvg_Colorspace) cs);
	if (result == TVG_RESULT_SUCCESS) {
		/* The canvas draws into this memory from now on: keep the string as long as the canvas. */
		handle = tvg_handle_from(Z_OBJ_P(canvas_zv));
		zval_ptr_dtor(&handle->keep);
		if (buffer != NULL) {
			ZVAL_STR_COPY(&handle->keep, buffer);
		} else {
			ZVAL_UNDEF(&handle->keep);
		}
	}
	RETURN_LONG((zend_long) result);
}

/* Binding addition: the alpha byte (bits 24..31 of each word) of a 32-bit canvas buffer, rows packed. */
ZEND_FUNCTION(tvg_swcanvas_get_alpha)
{
	zend_string *buffer = NULL, *alpha;
	zend_long address = 0, stride, w, h, cs;
	const void *bytes;
	const uint32_t *row;
	unsigned char *out;
	zend_long x, y;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR_OR_LONG(buffer, address)
		Z_PARAM_LONG(stride)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(stride, 2) || !tvg_u32(w, 3) || !tvg_u32(h, 4)) {
		RETURN_THROWS();
	}
	if (w > stride) {
		zend_argument_value_error(3, "must be at most the stride");
		RETURN_THROWS();
	}
	if (cs != TVG_COLORSPACE_ABGR8888 && cs != TVG_COLORSPACE_ARGB8888 && cs != TVG_COLORSPACE_ABGR8888S && cs != TVG_COLORSPACE_ARGB8888S) {
		zend_argument_value_error(5, "must be one of the four 32-bit TVG_COLORSPACE_* values with alpha");
		RETURN_THROWS();
	}
	if (!tvg_memory_arg(buffer, address, (size_t) stride * (size_t) h * 4, 1, &bytes)) {
		RETURN_THROWS();
	}

	if (bytes == NULL) {
		zend_argument_value_error(1, "must not be the address 0");
		RETURN_THROWS();
	}

	alpha = zend_string_safe_alloc((size_t) w, (size_t) h, 0, 0);
	out = (unsigned char *) ZSTR_VAL(alpha);
	for (y = 0; y < h; y++) {
		row = (const uint32_t *) bytes + (size_t) y * (size_t) stride;
		for (x = 0; x < w; x++) {
			*out++ = (unsigned char) (row[x] >> 24);
		}
	}
	ZSTR_VAL(alpha)[(size_t) w * (size_t) h] = '\0';
	RETURN_NEW_STR(alpha);
}

ZEND_FUNCTION(tvg_glcanvas_create)
{
	zend_long op;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(op)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(op, 0, TVG_ENGINE_OPTION_DEFAULT | TVG_ENGINE_OPTION_SMART_RENDER | TVG_ENGINE_OPTION_ALIASED, "a combination of TVG_ENGINE_OPTION_* flags", 1)) {
		RETURN_THROWS();
	}
	tvg_handle_new(TVG_K_CANVAS, tvg_glcanvas_create((Tvg_Engine_Option) op), return_value);
}

ZEND_FUNCTION(tvg_glcanvas_set_target)
{
	zval *canvas_zv;
	zend_long display, surface, context, id, w, h, cs;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_LONG(display)
		Z_PARAM_LONG(surface)
		Z_PARAM_LONG(context)
		Z_PARAM_LONG(id)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_i32(id, 5) || !tvg_u32(w, 6) || !tvg_u32(h, 7) || !tvg_colorspace_arg(cs, 8)) {
		RETURN_THROWS();
	}
	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	/* display, surface and context are addresses, trusted. */
	RETURN_LONG((zend_long) tvg_glcanvas_set_target(canvas, (void *) (uintptr_t) display, (void *) (uintptr_t) surface,
		(void *) (uintptr_t) context, (int32_t) id, (uint32_t) w, (uint32_t) h, (Tvg_Colorspace) cs));
}

ZEND_FUNCTION(tvg_wgcanvas_create)
{
	zend_long op;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(op)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(op, 0, TVG_ENGINE_OPTION_DEFAULT | TVG_ENGINE_OPTION_SMART_RENDER | TVG_ENGINE_OPTION_ALIASED, "a combination of TVG_ENGINE_OPTION_* flags", 1)) {
		RETURN_THROWS();
	}
	tvg_handle_new(TVG_K_CANVAS, tvg_wgcanvas_create((Tvg_Engine_Option) op), return_value);
}

ZEND_FUNCTION(tvg_wgcanvas_set_target)
{
	zval *canvas_zv;
	zend_long device, instance, target, w, h, cs, type;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(instance)
		Z_PARAM_LONG(target)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(w, 5) || !tvg_u32(h, 6) || !tvg_colorspace_arg(cs, 7) || !tvg_range(type, INT_MIN, INT_MAX, "an int", 8)) {
		RETURN_THROWS();
	}
	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	/* device, instance and target are addresses, trusted. */
	RETURN_LONG((zend_long) tvg_wgcanvas_set_target(canvas, (void *) (uintptr_t) device, (void *) (uintptr_t) instance,
		(void *) (uintptr_t) target, (uint32_t) w, (uint32_t) h, (Tvg_Colorspace) cs, (int) type));
}

ZEND_FUNCTION(tvg_wgcanvas_set_target_with_context)
{
	zval *canvas_zv;
	zend_object *context_obj;
	zend_long target, w, h, cs, type;
	Tvg_Canvas canvas;
	Tvg_WgContext context;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_OBJ_OF_CLASS(context_obj, tvg_wgcontext_ce)
		Z_PARAM_LONG(target)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
		Z_PARAM_LONG(type)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(w, 4) || !tvg_u32(h, 5) || !tvg_colorspace_arg(cs, 6) || !tvg_range(type, INT_MIN, INT_MAX, "an int", 7)) {
		RETURN_THROWS();
	}
	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	tvg_wgcontext_read(context_obj, &context);
	RETURN_LONG((zend_long) tvg_wgcanvas_set_target_with_context(canvas, &context, (void *) (uintptr_t) target,
		(uint32_t) w, (uint32_t) h, (Tvg_Colorspace) cs, (int) type));
}

ZEND_FUNCTION(tvg_canvas_destroy)
{
	zval *canvas_zv;
	Tvg_Canvas canvas;
	Tvg_Result result;
	tvg_handle_obj *handle;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	/* A draw may still be writing into the target, which the object stops keeping. */
	tvg_canvas_sync(canvas);
	result = tvg_canvas_destroy(canvas);
	handle = tvg_handle_from(Z_OBJ_P(canvas_zv));
	tvg_handle_release(Z_OBJ_P(canvas_zv));
	zval_ptr_dtor(&handle->keep);
	ZVAL_UNDEF(&handle->keep);
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_canvas_add)
{
	zval *canvas_zv, *paint_zv;
	Tvg_Canvas canvas;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, tvg_handle_ce[TVG_K_PAINT])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_add(canvas, paint));
}

ZEND_FUNCTION(tvg_canvas_insert)
{
	zval *canvas_zv, *target_zv, *at_zv = NULL;
	Tvg_Canvas canvas;
	Tvg_Paint target, at = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_OBJECT_OF_CLASS(target_zv, tvg_handle_ce[TVG_K_PAINT])
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(at_zv, tvg_handle_ce[TVG_K_PAINT])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	target = tvg_paint_arg(target_zv, TVG_TYPE_UNDEF, 2);
	if (target == NULL) {
		RETURN_THROWS();
	}
	if (at_zv != NULL && (at = tvg_paint_arg(at_zv, TVG_TYPE_UNDEF, 3)) == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_insert(canvas, target, at));
}

ZEND_FUNCTION(tvg_canvas_remove)
{
	zval *canvas_zv, *paint_zv;
	Tvg_Canvas canvas;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, tvg_handle_ce[TVG_K_PAINT])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_remove(canvas, paint));
}

ZEND_FUNCTION(tvg_canvas_update)
{
	zval *canvas_zv;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_update(canvas));
}

ZEND_FUNCTION(tvg_canvas_draw)
{
	zval *canvas_zv;
	bool clear;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_BOOL(clear)
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_draw(canvas, clear));
}

ZEND_FUNCTION(tvg_canvas_sync)
{
	zval *canvas_zv;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_sync(canvas));
}

ZEND_FUNCTION(tvg_canvas_get_dirty_regions_cnt)
{
	zval *canvas_zv;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_get_dirty_regions_cnt(canvas));
}

ZEND_FUNCTION(tvg_canvas_get_dirty_regions)
{
	zval *canvas_zv, *regions_zv, item;
	zend_long cnt;
	Tvg_Canvas canvas;
	Tvg_Region *regions;
	Tvg_Result result;
	uint32_t available, i;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_ZVAL(regions_zv)
		Z_PARAM_LONG(cnt)
	ZEND_PARSE_PARAMETERS_END();

	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	/* The C caller sizes the array from tvg_canvas_get_dirty_regions_cnt(): so does this one. */
	available = tvg_canvas_get_dirty_regions_cnt(canvas);
	if (!tvg_range(cnt, 0, available, "between 0 and tvg_canvas_get_dirty_regions_cnt()", 3)) {
		RETURN_THROWS();
	}
	regions = cnt > 0 ? safe_emalloc((size_t) cnt, sizeof(Tvg_Region), 0) : NULL;
	if (regions != NULL) {
		memset(regions, 0, (size_t) cnt * sizeof(Tvg_Region));
	}
	result = tvg_canvas_get_dirty_regions(canvas, regions, (uint32_t) cnt);
	array_init_size(&item, (uint32_t) cnt);
	for (i = 0; i < (uint32_t) cnt; i++) {
		zval region;
		tvg_region_new(&regions[i], &region);
		zend_hash_next_index_insert_new(Z_ARRVAL(item), &region);
	}
	if (regions != NULL) {
		efree(regions);
	}
	ZEND_TRY_ASSIGN_REF_VALUE(regions_zv, &item);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_canvas_set_viewport)
{
	zval *canvas_zv;
	zend_long x, y, w, h;
	Tvg_Canvas canvas;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(canvas_zv, tvg_handle_ce[TVG_K_CANVAS])
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_i32(x, 2) || !tvg_i32(y, 3) || !tvg_i32(w, 4) || !tvg_i32(h, 5)) {
		RETURN_THROWS();
	}
	canvas = tvg_canvas_arg(canvas_zv, 1);
	if (canvas == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_canvas_set_viewport(canvas, (int32_t) x, (int32_t) y, (int32_t) w, (int32_t) h));
}

void tvg_canvas_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
