/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: c4c20bf91bf7658cb2fc2a54dfd3b91cc5d9c3cb */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_linear_gradient_new, 0, 0, Tvg_Gradient, 1)
ZEND_END_ARG_INFO()

#define arginfo_tvg_radial_gradient_new arginfo_tvg_linear_gradient_new

#define arginfo_tvg_conic_gradient_new arginfo_tvg_linear_gradient_new

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_linear_gradient_set, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_linear_gradient_get, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, x1, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, y1, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, x2, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, y2, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_radial_gradient_set, 0, 7, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, fx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, fy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, fr, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_radial_gradient_get, 0, 7, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, cx, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, cy, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, r, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, fx, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, fy, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, fr, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_conic_gradient_set, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_conic_gradient_get, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, cx, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, cy, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, angle, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_set_color_stops, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(0, color_stop, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, cnt, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_get_color_stops, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, color_stop, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, cnt, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_set_spread, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(0, spread, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_get_spread, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, spread, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_set_transform, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_OBJ_INFO(0, m, Tvg_Matrix, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_gradient_get_transform arginfo_tvg_gradient_set_transform

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_get_type, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
	ZEND_ARG_TYPE_INFO(1, type, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_gradient_duplicate, 0, 1, Tvg_Gradient, 1)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_gradient_del, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(tvg_linear_gradient_new);
ZEND_FUNCTION(tvg_radial_gradient_new);
ZEND_FUNCTION(tvg_conic_gradient_new);
ZEND_FUNCTION(tvg_linear_gradient_set);
ZEND_FUNCTION(tvg_linear_gradient_get);
ZEND_FUNCTION(tvg_radial_gradient_set);
ZEND_FUNCTION(tvg_radial_gradient_get);
ZEND_FUNCTION(tvg_conic_gradient_set);
ZEND_FUNCTION(tvg_conic_gradient_get);
ZEND_FUNCTION(tvg_gradient_set_color_stops);
ZEND_FUNCTION(tvg_gradient_get_color_stops);
ZEND_FUNCTION(tvg_gradient_set_spread);
ZEND_FUNCTION(tvg_gradient_get_spread);
ZEND_FUNCTION(tvg_gradient_set_transform);
ZEND_FUNCTION(tvg_gradient_get_transform);
ZEND_FUNCTION(tvg_gradient_get_type);
ZEND_FUNCTION(tvg_gradient_duplicate);
ZEND_FUNCTION(tvg_gradient_del);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_linear_gradient_new, arginfo_tvg_linear_gradient_new)
	ZEND_FE(tvg_radial_gradient_new, arginfo_tvg_radial_gradient_new)
	ZEND_FE(tvg_conic_gradient_new, arginfo_tvg_conic_gradient_new)
	ZEND_FE(tvg_linear_gradient_set, arginfo_tvg_linear_gradient_set)
	ZEND_FE(tvg_linear_gradient_get, arginfo_tvg_linear_gradient_get)
	ZEND_FE(tvg_radial_gradient_set, arginfo_tvg_radial_gradient_set)
	ZEND_FE(tvg_radial_gradient_get, arginfo_tvg_radial_gradient_get)
	ZEND_FE(tvg_conic_gradient_set, arginfo_tvg_conic_gradient_set)
	ZEND_FE(tvg_conic_gradient_get, arginfo_tvg_conic_gradient_get)
	ZEND_FE(tvg_gradient_set_color_stops, arginfo_tvg_gradient_set_color_stops)
	ZEND_FE(tvg_gradient_get_color_stops, arginfo_tvg_gradient_get_color_stops)
	ZEND_FE(tvg_gradient_set_spread, arginfo_tvg_gradient_set_spread)
	ZEND_FE(tvg_gradient_get_spread, arginfo_tvg_gradient_get_spread)
	ZEND_FE(tvg_gradient_set_transform, arginfo_tvg_gradient_set_transform)
	ZEND_FE(tvg_gradient_get_transform, arginfo_tvg_gradient_get_transform)
	ZEND_FE(tvg_gradient_get_type, arginfo_tvg_gradient_get_type)
	ZEND_FE(tvg_gradient_duplicate, arginfo_tvg_gradient_duplicate)
	ZEND_FE(tvg_gradient_del, arginfo_tvg_gradient_del)
	ZEND_FE_END
};
