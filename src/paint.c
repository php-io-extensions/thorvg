/*
 * Paint bindings (thorvg_paint.stub.php): what every shape, scene, picture and text shares.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_paint_arginfo.h"

#define PAINT_CE tvg_handle_ce[TVG_K_PAINT]

ZEND_FUNCTION(tvg_paint_rel)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	/* The object's reference keeps the count above zero, so ThorVG frees nothing here. */
	RETURN_LONG((zend_long) tvg_paint_rel(paint));
}

ZEND_FUNCTION(tvg_paint_ref)
{
	zval *paint_zv;
	Tvg_Paint paint;
	uint16_t count;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	if (tvg_paint_get_ref(paint) == UINT16_MAX) {
		zend_argument_value_error(1, "already has the most references a paint can count (65535)");
		RETURN_THROWS();
	}
	count = tvg_paint_ref(paint);
	tvg_handle_from(Z_OBJ_P(paint_zv))->user_refs++;
	RETURN_LONG((zend_long) count);
}

ZEND_FUNCTION(tvg_paint_unref)
{
	zval *paint_zv;
	bool free_it;
	Tvg_Paint paint;
	tvg_handle_obj *handle;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_BOOL(free_it)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	handle = tvg_handle_from(Z_OBJ_P(paint_zv));
	if (handle->user_refs == 0) {
		/* The remaining reference is the object's own: giving it back would free a paint PHP holds. */
		zend_argument_value_error(1, "has no reference taken by tvg_paint_ref() to give back");
		RETURN_THROWS();
	}
	handle->user_refs--;
	RETURN_LONG((zend_long) tvg_paint_unref(paint, free_it));
}

ZEND_FUNCTION(tvg_paint_get_ref)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_get_ref(paint));
}

ZEND_FUNCTION(tvg_paint_set_visible)
{
	zval *paint_zv;
	bool visible;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_BOOL(visible)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_visible(paint, visible));
}

ZEND_FUNCTION(tvg_paint_get_visible)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_BOOL(tvg_paint_get_visible(paint));
}

ZEND_FUNCTION(tvg_paint_get_id)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_get_id(paint));
}

ZEND_FUNCTION(tvg_paint_set_id)
{
	zval *paint_zv;
	zend_long id;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(id, 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_id(paint, (uint32_t) id));
}

ZEND_FUNCTION(tvg_paint_get_data)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) (uintptr_t) tvg_paint_get_data(paint));
}

ZEND_FUNCTION(tvg_paint_set_data)
{
	zval *paint_zv;
	zend_long data;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(data)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	/* An address, trusted; ThorVG only stores it. */
	RETURN_LONG((zend_long) tvg_paint_set_data(paint, (void *) (uintptr_t) data));
}

ZEND_FUNCTION(tvg_paint_scale)
{
	zval *paint_zv;
	double factor;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(factor)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_scale(paint, (float) factor));
}

ZEND_FUNCTION(tvg_paint_rotate)
{
	zval *paint_zv;
	double degree;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(degree)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_rotate(paint, (float) degree));
}

ZEND_FUNCTION(tvg_paint_translate)
{
	zval *paint_zv;
	double x, y;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_translate(paint, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_paint_set_transform)
{
	zval *paint_zv;
	zend_object *m_obj;
	Tvg_Paint paint;
	Tvg_Matrix m;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJ_OF_CLASS(m_obj, tvg_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	tvg_matrix_read(m_obj, &m);
	RETURN_LONG((zend_long) tvg_paint_set_transform(paint, &m));
}

ZEND_FUNCTION(tvg_paint_get_transform)
{
	zval *paint_zv;
	zend_object *m_obj;
	Tvg_Paint paint;
	Tvg_Matrix m;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJ_OF_CLASS(m_obj, tvg_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	memset(&m, 0, sizeof(m));
	result = tvg_paint_get_transform(paint, &m);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_matrix_write(m_obj, &m);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_set_opacity)
{
	zval *paint_zv;
	zend_long opacity;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(opacity)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u8(opacity, 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_opacity(paint, (uint8_t) opacity));
}

ZEND_FUNCTION(tvg_paint_get_opacity)
{
	zval *paint_zv, *opacity_zv;
	Tvg_Paint paint;
	uint8_t opacity = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(opacity_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_paint_get_opacity(paint, &opacity);
	TVG_REF_LONG(opacity_zv, opacity);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_duplicate)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_paint_duplicate(paint), return_value);
}

ZEND_FUNCTION(tvg_paint_intersects)
{
	zval *paint_zv;
	zend_long x, y, w, h;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_i32(x, 2) || !tvg_i32(y, 3) || !tvg_i32(w, 4) || !tvg_i32(h, 5)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_BOOL(tvg_paint_intersects(paint, (int32_t) x, (int32_t) y, (int32_t) w, (int32_t) h));
}

ZEND_FUNCTION(tvg_paint_intersects_region)
{
	zval *paint_zv;
	zend_long x, y, w, h;
	bool visible_only;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_BOOL(visible_only)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_i32(x, 2) || !tvg_i32(y, 3) || !tvg_i32(w, 4) || !tvg_i32(h, 5)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_BOOL(tvg_paint_intersects_region(paint, (int32_t) x, (int32_t) y, (int32_t) w, (int32_t) h, visible_only));
}

ZEND_FUNCTION(tvg_paint_get_aabb)
{
	zval *paint_zv, *x_zv, *y_zv, *w_zv, *h_zv;
	Tvg_Paint paint;
	float x = 0, y = 0, w = 0, h = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(x_zv)
		Z_PARAM_ZVAL(y_zv)
		Z_PARAM_ZVAL(w_zv)
		Z_PARAM_ZVAL(h_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_paint_get_aabb(paint, &x, &y, &w, &h);
	TVG_REF_DOUBLE(x_zv, x);
	TVG_REF_DOUBLE(y_zv, y);
	TVG_REF_DOUBLE(w_zv, w);
	TVG_REF_DOUBLE(h_zv, h);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_get_obb)
{
	zval *paint_zv, *pt4_zv, list;
	Tvg_Paint paint;
	Tvg_Point pt4[4];
	Tvg_Result result;
	int i;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(pt4_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	memset(pt4, 0, sizeof(pt4));
	result = tvg_paint_get_obb(paint, pt4);
	array_init_size(&list, 4);
	for (i = 0; i < 4; i++) {
		zval point;
		tvg_point_new(&pt4[i], &point);
		zend_hash_next_index_insert_new(Z_ARRVAL(list), &point);
	}
	ZEND_TRY_ASSIGN_REF_VALUE(pt4_zv, &list);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_set_mask_method)
{
	zval *paint_zv, *target_zv = NULL;
	zend_long method;
	Tvg_Paint paint, target = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(target_zv, PAINT_CE)
		Z_PARAM_LONG(method)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(method, TVG_MASK_METHOD_NONE, TVG_MASK_METHOD_DARKEN, "a TVG_MASK_METHOD_* value", 3)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	if (target_zv != NULL && (target = tvg_paint_arg(target_zv, TVG_TYPE_UNDEF, 2)) == NULL) {
		RETURN_THROWS();
	}
	if (target == NULL && method != TVG_MASK_METHOD_NONE) {
		/* ThorVG takes a reference on the target unchecked when the method is not None. */
		zend_argument_value_error(2, "must be a paint unless the method is TVG_MASK_METHOD_NONE");
		RETURN_THROWS();
	}
	if (target == paint) {
		zend_argument_value_error(2, "must not be the paint itself");
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_mask_method(paint, target, (Tvg_Mask_Method) method));
}

ZEND_FUNCTION(tvg_paint_get_mask_method)
{
	zval *paint_zv, *target_zv, *method_zv, target_obj;
	Tvg_Paint paint, target = NULL;
	Tvg_Mask_Method method = TVG_MASK_METHOD_NONE;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(target_zv)
		Z_PARAM_ZVAL(method_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	/*
	 * ThorVG writes the target's address through `target` (documented [out], typed as a paint):
	 * handing it a paint would overwrite that paint's first word. It gets a local to write into.
	 */
	result = tvg_paint_get_mask_method(paint, (Tvg_Paint) &target, &method);
	tvg_paint_wrap(result == TVG_RESULT_SUCCESS ? target : NULL, &target_obj);
	ZEND_TRY_ASSIGN_REF_VALUE(target_zv, &target_obj);
	TVG_REF_LONG(method_zv, method);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_set_clip)
{
	zval *paint_zv, *clipper_zv = NULL;
	Tvg_Paint paint, clipper = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(clipper_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	/* ThorVG casts the clipper to a shape unchecked. */
	if (clipper_zv != NULL && (clipper = tvg_paint_arg(clipper_zv, TVG_TYPE_SHAPE, 2)) == NULL) {
		RETURN_THROWS();
	}
	if (clipper == paint) {
		zend_argument_value_error(2, "must not be the paint itself");
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_clip(paint, clipper));
}

ZEND_FUNCTION(tvg_paint_get_clip)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_paint_get_clip(paint), return_value);
}

ZEND_FUNCTION(tvg_paint_get_parent)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_paint_get_parent(paint), return_value);
}

ZEND_FUNCTION(tvg_paint_get_type)
{
	zval *paint_zv, *type_zv;
	Tvg_Paint paint;
	Tvg_Type type = TVG_TYPE_UNDEF;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(type_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_paint_get_type(paint, &type);
	TVG_REF_LONG(type_zv, type);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_paint_set_blend_method)
{
	zval *paint_zv;
	zend_long method;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(method)
	ZEND_PARSE_PARAMETERS_END();

	if (!((method >= TVG_BLEND_METHOD_NORMAL && method <= TVG_BLEND_METHOD_ADD) || method == TVG_BLEND_METHOD_COMPOSITION)) {
		zend_argument_value_error(2, "must be a TVG_BLEND_METHOD_* value");
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_paint_set_blend_method(paint, (Tvg_Blend_Method) method));
}

void tvg_paint_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
