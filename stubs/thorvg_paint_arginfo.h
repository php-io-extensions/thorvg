/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 874a1e530fc65d503e639d749764e787d90f63c2 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_rel, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_ref arginfo_tvg_paint_rel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_unref, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, free, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_get_ref arginfo_tvg_paint_rel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_visible, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, visible, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_visible, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_get_id arginfo_tvg_paint_rel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_id, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_get_data arginfo_tvg_paint_rel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_data, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_scale, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_rotate, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, degree, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_translate, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_transform, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, m, Tvg_Matrix, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_get_transform arginfo_tvg_paint_set_transform

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_opacity, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_opacity, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, opacity, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_paint_duplicate, 0, 1, Tvg_Paint, 1)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_intersects, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_intersects_region, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, visibleOnly, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_aabb, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, x, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, y, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, w, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, h, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_obb, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, pt4, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_mask_method, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, target, Tvg_Paint, 1)
	ZEND_ARG_TYPE_INFO(0, method, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_mask_method, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(1, target, Tvg_Paint, 1)
	ZEND_ARG_TYPE_INFO(1, method, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_clip, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, clipper, Tvg_Paint, 1)
ZEND_END_ARG_INFO()

#define arginfo_tvg_paint_get_clip arginfo_tvg_paint_duplicate

#define arginfo_tvg_paint_get_parent arginfo_tvg_paint_duplicate

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_get_type, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, type, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_paint_set_blend_method, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, method, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(tvg_paint_rel);
ZEND_FUNCTION(tvg_paint_ref);
ZEND_FUNCTION(tvg_paint_unref);
ZEND_FUNCTION(tvg_paint_get_ref);
ZEND_FUNCTION(tvg_paint_set_visible);
ZEND_FUNCTION(tvg_paint_get_visible);
ZEND_FUNCTION(tvg_paint_get_id);
ZEND_FUNCTION(tvg_paint_set_id);
ZEND_FUNCTION(tvg_paint_get_data);
ZEND_FUNCTION(tvg_paint_set_data);
ZEND_FUNCTION(tvg_paint_scale);
ZEND_FUNCTION(tvg_paint_rotate);
ZEND_FUNCTION(tvg_paint_translate);
ZEND_FUNCTION(tvg_paint_set_transform);
ZEND_FUNCTION(tvg_paint_get_transform);
ZEND_FUNCTION(tvg_paint_set_opacity);
ZEND_FUNCTION(tvg_paint_get_opacity);
ZEND_FUNCTION(tvg_paint_duplicate);
ZEND_FUNCTION(tvg_paint_intersects);
ZEND_FUNCTION(tvg_paint_intersects_region);
ZEND_FUNCTION(tvg_paint_get_aabb);
ZEND_FUNCTION(tvg_paint_get_obb);
ZEND_FUNCTION(tvg_paint_set_mask_method);
ZEND_FUNCTION(tvg_paint_get_mask_method);
ZEND_FUNCTION(tvg_paint_set_clip);
ZEND_FUNCTION(tvg_paint_get_clip);
ZEND_FUNCTION(tvg_paint_get_parent);
ZEND_FUNCTION(tvg_paint_get_type);
ZEND_FUNCTION(tvg_paint_set_blend_method);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_paint_rel, arginfo_tvg_paint_rel)
	ZEND_FE(tvg_paint_ref, arginfo_tvg_paint_ref)
	ZEND_FE(tvg_paint_unref, arginfo_tvg_paint_unref)
	ZEND_FE(tvg_paint_get_ref, arginfo_tvg_paint_get_ref)
	ZEND_FE(tvg_paint_set_visible, arginfo_tvg_paint_set_visible)
	ZEND_FE(tvg_paint_get_visible, arginfo_tvg_paint_get_visible)
	ZEND_FE(tvg_paint_get_id, arginfo_tvg_paint_get_id)
	ZEND_FE(tvg_paint_set_id, arginfo_tvg_paint_set_id)
	ZEND_FE(tvg_paint_get_data, arginfo_tvg_paint_get_data)
	ZEND_FE(tvg_paint_set_data, arginfo_tvg_paint_set_data)
	ZEND_FE(tvg_paint_scale, arginfo_tvg_paint_scale)
	ZEND_FE(tvg_paint_rotate, arginfo_tvg_paint_rotate)
	ZEND_FE(tvg_paint_translate, arginfo_tvg_paint_translate)
	ZEND_FE(tvg_paint_set_transform, arginfo_tvg_paint_set_transform)
	ZEND_FE(tvg_paint_get_transform, arginfo_tvg_paint_get_transform)
	ZEND_FE(tvg_paint_set_opacity, arginfo_tvg_paint_set_opacity)
	ZEND_FE(tvg_paint_get_opacity, arginfo_tvg_paint_get_opacity)
	ZEND_FE(tvg_paint_duplicate, arginfo_tvg_paint_duplicate)
	ZEND_FE(tvg_paint_intersects, arginfo_tvg_paint_intersects)
	ZEND_FE(tvg_paint_intersects_region, arginfo_tvg_paint_intersects_region)
	ZEND_FE(tvg_paint_get_aabb, arginfo_tvg_paint_get_aabb)
	ZEND_FE(tvg_paint_get_obb, arginfo_tvg_paint_get_obb)
	ZEND_FE(tvg_paint_set_mask_method, arginfo_tvg_paint_set_mask_method)
	ZEND_FE(tvg_paint_get_mask_method, arginfo_tvg_paint_get_mask_method)
	ZEND_FE(tvg_paint_set_clip, arginfo_tvg_paint_set_clip)
	ZEND_FE(tvg_paint_get_clip, arginfo_tvg_paint_get_clip)
	ZEND_FE(tvg_paint_get_parent, arginfo_tvg_paint_get_parent)
	ZEND_FE(tvg_paint_get_type, arginfo_tvg_paint_get_type)
	ZEND_FE(tvg_paint_set_blend_method, arginfo_tvg_paint_set_blend_method)
	ZEND_FE_END
};
