/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 240fdbbe1aea582b7db04277d47da44097cbdbc0 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_shape_new, 0, 0, Tvg_Paint, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_reset, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_move_to, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_shape_line_to arginfo_tvg_shape_move_to

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_cubic_to, 0, 7, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, cx1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cx2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_shape_close arginfo_tvg_shape_reset

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_append_rect, 0, 8, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cw, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_append_circle, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cw, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_append_path, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, cmds, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, cmdCnt, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pts, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, ptsCnt, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_path, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, cmds, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, cmdsCnt, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, pts, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, ptsCnt, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_width, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_width, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, width, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_color, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_color, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, r, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, g, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, b, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, a, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_gradient, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, grad, Tvg_Gradient, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_gradient, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(1, grad, Tvg_Gradient, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_dash, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, dashPattern, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, cnt, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_dash, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, dashPattern, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, cnt, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, offset, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_cap, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, cap, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_cap, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, cap, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_join, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, join, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_join, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, join, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_stroke_miterlimit, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, miterlimit, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_stroke_miterlimit, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, miterlimit, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_trimpath, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, begin, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, end, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, simultaneous, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_shape_set_fill_color arginfo_tvg_shape_set_stroke_color

#define arginfo_tvg_shape_get_fill_color arginfo_tvg_shape_get_stroke_color

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_fill_rule, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, rule, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_get_fill_rule, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, rule, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_shape_set_paint_order, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, strokeFirst, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_shape_set_gradient arginfo_tvg_shape_set_stroke_gradient

#define arginfo_tvg_shape_get_gradient arginfo_tvg_shape_get_stroke_gradient

ZEND_FUNCTION(tvg_shape_new);
ZEND_FUNCTION(tvg_shape_reset);
ZEND_FUNCTION(tvg_shape_move_to);
ZEND_FUNCTION(tvg_shape_line_to);
ZEND_FUNCTION(tvg_shape_cubic_to);
ZEND_FUNCTION(tvg_shape_close);
ZEND_FUNCTION(tvg_shape_append_rect);
ZEND_FUNCTION(tvg_shape_append_circle);
ZEND_FUNCTION(tvg_shape_append_path);
ZEND_FUNCTION(tvg_shape_get_path);
ZEND_FUNCTION(tvg_shape_set_stroke_width);
ZEND_FUNCTION(tvg_shape_get_stroke_width);
ZEND_FUNCTION(tvg_shape_set_stroke_color);
ZEND_FUNCTION(tvg_shape_get_stroke_color);
ZEND_FUNCTION(tvg_shape_set_stroke_gradient);
ZEND_FUNCTION(tvg_shape_get_stroke_gradient);
ZEND_FUNCTION(tvg_shape_set_stroke_dash);
ZEND_FUNCTION(tvg_shape_get_stroke_dash);
ZEND_FUNCTION(tvg_shape_set_stroke_cap);
ZEND_FUNCTION(tvg_shape_get_stroke_cap);
ZEND_FUNCTION(tvg_shape_set_stroke_join);
ZEND_FUNCTION(tvg_shape_get_stroke_join);
ZEND_FUNCTION(tvg_shape_set_stroke_miterlimit);
ZEND_FUNCTION(tvg_shape_get_stroke_miterlimit);
ZEND_FUNCTION(tvg_shape_set_trimpath);
ZEND_FUNCTION(tvg_shape_set_fill_color);
ZEND_FUNCTION(tvg_shape_get_fill_color);
ZEND_FUNCTION(tvg_shape_set_fill_rule);
ZEND_FUNCTION(tvg_shape_get_fill_rule);
ZEND_FUNCTION(tvg_shape_set_paint_order);
ZEND_FUNCTION(tvg_shape_set_gradient);
ZEND_FUNCTION(tvg_shape_get_gradient);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_shape_new, arginfo_tvg_shape_new)
	ZEND_FE(tvg_shape_reset, arginfo_tvg_shape_reset)
	ZEND_FE(tvg_shape_move_to, arginfo_tvg_shape_move_to)
	ZEND_FE(tvg_shape_line_to, arginfo_tvg_shape_line_to)
	ZEND_FE(tvg_shape_cubic_to, arginfo_tvg_shape_cubic_to)
	ZEND_FE(tvg_shape_close, arginfo_tvg_shape_close)
	ZEND_FE(tvg_shape_append_rect, arginfo_tvg_shape_append_rect)
	ZEND_FE(tvg_shape_append_circle, arginfo_tvg_shape_append_circle)
	ZEND_FE(tvg_shape_append_path, arginfo_tvg_shape_append_path)
	ZEND_FE(tvg_shape_get_path, arginfo_tvg_shape_get_path)
	ZEND_FE(tvg_shape_set_stroke_width, arginfo_tvg_shape_set_stroke_width)
	ZEND_FE(tvg_shape_get_stroke_width, arginfo_tvg_shape_get_stroke_width)
	ZEND_FE(tvg_shape_set_stroke_color, arginfo_tvg_shape_set_stroke_color)
	ZEND_FE(tvg_shape_get_stroke_color, arginfo_tvg_shape_get_stroke_color)
	ZEND_FE(tvg_shape_set_stroke_gradient, arginfo_tvg_shape_set_stroke_gradient)
	ZEND_FE(tvg_shape_get_stroke_gradient, arginfo_tvg_shape_get_stroke_gradient)
	ZEND_FE(tvg_shape_set_stroke_dash, arginfo_tvg_shape_set_stroke_dash)
	ZEND_FE(tvg_shape_get_stroke_dash, arginfo_tvg_shape_get_stroke_dash)
	ZEND_FE(tvg_shape_set_stroke_cap, arginfo_tvg_shape_set_stroke_cap)
	ZEND_FE(tvg_shape_get_stroke_cap, arginfo_tvg_shape_get_stroke_cap)
	ZEND_FE(tvg_shape_set_stroke_join, arginfo_tvg_shape_set_stroke_join)
	ZEND_FE(tvg_shape_get_stroke_join, arginfo_tvg_shape_get_stroke_join)
	ZEND_FE(tvg_shape_set_stroke_miterlimit, arginfo_tvg_shape_set_stroke_miterlimit)
	ZEND_FE(tvg_shape_get_stroke_miterlimit, arginfo_tvg_shape_get_stroke_miterlimit)
	ZEND_FE(tvg_shape_set_trimpath, arginfo_tvg_shape_set_trimpath)
	ZEND_FE(tvg_shape_set_fill_color, arginfo_tvg_shape_set_fill_color)
	ZEND_FE(tvg_shape_get_fill_color, arginfo_tvg_shape_get_fill_color)
	ZEND_FE(tvg_shape_set_fill_rule, arginfo_tvg_shape_set_fill_rule)
	ZEND_FE(tvg_shape_get_fill_rule, arginfo_tvg_shape_get_fill_rule)
	ZEND_FE(tvg_shape_set_paint_order, arginfo_tvg_shape_set_paint_order)
	ZEND_FE(tvg_shape_set_gradient, arginfo_tvg_shape_set_gradient)
	ZEND_FE(tvg_shape_get_gradient, arginfo_tvg_shape_get_gradient)
	ZEND_FE_END
};
