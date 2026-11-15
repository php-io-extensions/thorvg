/*
 * Shape bindings (thorvg_shape.stub.php). Every function checks its paint is a shape:
 * ThorVG casts it unchecked.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_shape_arginfo.h"

#define PAINT_CE tvg_handle_ce[TVG_K_PAINT]
#define GRADIENT_CE tvg_handle_ce[TVG_K_GRADIENT]

/* r, g, b, a arguments at positions first..first+3. */
static bool tvg_rgba_args(zend_long r, zend_long g, zend_long b, zend_long a, uint32_t first)
{
	return tvg_u8(r, first) && tvg_u8(g, first + 1) && tvg_u8(b, first + 2) && tvg_u8(a, first + 3);
}

ZEND_FUNCTION(tvg_shape_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_paint_wrap(tvg_shape_new(), return_value);
}

ZEND_FUNCTION(tvg_shape_reset)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_reset(paint));
}

ZEND_FUNCTION(tvg_shape_move_to)
{
	zval *paint_zv;
	double x, y;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	{
		const double v[] = {x, y};
		if (!tvg_finite_args(v, 2, 2)) {
			RETURN_THROWS();
		}
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_move_to(paint, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_shape_line_to)
{
	zval *paint_zv;
	double x, y;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	{
		const double v[] = {x, y};
		if (!tvg_finite_args(v, 2, 2)) {
			RETURN_THROWS();
		}
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_line_to(paint, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_shape_cubic_to)
{
	zval *paint_zv;
	double cx1, cy1, cx2, cy2, x, y;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(cx1)
		Z_PARAM_DOUBLE(cy1)
		Z_PARAM_DOUBLE(cx2)
		Z_PARAM_DOUBLE(cy2)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	{
		const double v[] = {cx1, cy1, cx2, cy2, x, y};
		if (!tvg_finite_args(v, 6, 2)) {
			RETURN_THROWS();
		}
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_cubic_to(paint, (float) cx1, (float) cy1, (float) cx2, (float) cy2, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_shape_close)
{
	zval *paint_zv;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_close(paint));
}

ZEND_FUNCTION(tvg_shape_append_rect)
{
	zval *paint_zv;
	double x, y, w, h, rx, ry;
	bool cw;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
		Z_PARAM_DOUBLE(rx)
		Z_PARAM_DOUBLE(ry)
		Z_PARAM_BOOL(cw)
	ZEND_PARSE_PARAMETERS_END();

	{
		const double v[] = {x, y, w, h, rx, ry};
		if (!tvg_finite_args(v, 6, 2)) {
			RETURN_THROWS();
		}
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_append_rect(paint, (float) x, (float) y, (float) w, (float) h, (float) rx, (float) ry, cw));
}

ZEND_FUNCTION(tvg_shape_append_circle)
{
	zval *paint_zv;
	double cx, cy, rx, ry;
	bool cw;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(cx)
		Z_PARAM_DOUBLE(cy)
		Z_PARAM_DOUBLE(rx)
		Z_PARAM_DOUBLE(ry)
		Z_PARAM_BOOL(cw)
	ZEND_PARSE_PARAMETERS_END();

	{
		const double v[] = {cx, cy, rx, ry};
		if (!tvg_finite_args(v, 4, 2)) {
			RETURN_THROWS();
		}
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_append_circle(paint, (float) cx, (float) cy, (float) rx, (float) ry, cw));
}

ZEND_FUNCTION(tvg_shape_append_path)
{
	zval *paint_zv;
	HashTable *cmds_ht, *pts_ht;
	zend_long cmd_cnt, pts_cnt;
	Tvg_Paint paint;
	Tvg_Path_Command *cmds;
	Tvg_Point *pts;
	bool ok;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ARRAY_HT(cmds_ht)
		Z_PARAM_LONG(cmd_cnt)
		Z_PARAM_ARRAY_HT(pts_ht)
		Z_PARAM_LONG(pts_cnt)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_list_count(cmds_ht, cmd_cnt, 3) || !tvg_list_count(pts_ht, pts_cnt, 5)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	cmds = tvg_commands_read(cmds_ht, cmd_cnt, 2, &ok);
	if (!ok) {
		RETURN_THROWS();
	}
	pts = tvg_points_read(pts_ht, pts_cnt, 4, &ok);
	if (!ok) {
		if (cmds != NULL) {
			efree(cmds);
		}
		RETURN_THROWS();
	}
	result = tvg_shape_append_path(paint, cmds, (uint32_t) cmd_cnt, pts, (uint32_t) pts_cnt);
	if (cmds != NULL) {
		efree(cmds);
	}
	if (pts != NULL) {
		efree(pts);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_get_path)
{
	zval *paint_zv, *cmds_zv, *cmds_cnt_zv, *pts_zv, *pts_cnt_zv, cmds_list, pts_list;
	Tvg_Paint paint;
	const Tvg_Path_Command *cmds = NULL;
	const Tvg_Point *pts = NULL;
	uint32_t cmds_cnt = 0, pts_cnt = 0, i;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(cmds_zv)
		Z_PARAM_ZVAL(cmds_cnt_zv)
		Z_PARAM_ZVAL(pts_zv)
		Z_PARAM_ZVAL(pts_cnt_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_path(paint, &cmds, &cmds_cnt, &pts, &pts_cnt);
	if (result != TVG_RESULT_SUCCESS || cmds == NULL) {
		cmds_cnt = 0;
	}
	if (result != TVG_RESULT_SUCCESS || pts == NULL) {
		pts_cnt = 0;
	}
	array_init_size(&cmds_list, cmds_cnt);
	for (i = 0; i < cmds_cnt; i++) {
		add_next_index_long(&cmds_list, (zend_long) cmds[i]);
	}
	array_init_size(&pts_list, pts_cnt);
	for (i = 0; i < pts_cnt; i++) {
		zval point;
		tvg_point_new(&pts[i], &point);
		zend_hash_next_index_insert_new(Z_ARRVAL(pts_list), &point);
	}
	ZEND_TRY_ASSIGN_REF_VALUE(cmds_zv, &cmds_list);
	TVG_REF_LONG(cmds_cnt_zv, cmds_cnt);
	ZEND_TRY_ASSIGN_REF_VALUE(pts_zv, &pts_list);
	TVG_REF_LONG(pts_cnt_zv, pts_cnt);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

extern int tvgphp_stroke_outline(const void *paint, uint8_t **cmds, uint32_t *cmd_cnt, float **xy, uint32_t *pt_cnt);

/* Binding addition: see src/stroke_outline.cpp. */
ZEND_FUNCTION(tvg_shape_get_stroke_outline)
{
	zval *paint_zv, *cmds_zv, *cmds_cnt_zv, *pts_zv, *pts_cnt_zv, cmds_list, pts_list;
	Tvg_Paint paint;
	uint8_t *cmds;
	float *xy;
	uint32_t cmds_cnt, pts_cnt, i;
	int result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(cmds_zv)
		Z_PARAM_ZVAL(cmds_cnt_zv)
		Z_PARAM_ZVAL(pts_zv)
		Z_PARAM_ZVAL(pts_cnt_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvgphp_stroke_outline(paint, &cmds, &cmds_cnt, &xy, &pts_cnt);
	array_init_size(&cmds_list, cmds_cnt);
	for (i = 0; i < cmds_cnt; i++) {
		add_next_index_long(&cmds_list, (zend_long) cmds[i]);
	}
	array_init_size(&pts_list, pts_cnt);
	for (i = 0; i < pts_cnt; i++) {
		zval point;
		Tvg_Point p = { xy[2 * i], xy[2 * i + 1] };
		tvg_point_new(&p, &point);
		zend_hash_next_index_insert_new(Z_ARRVAL(pts_list), &point);
	}
	free(cmds);
	free(xy);
	ZEND_TRY_ASSIGN_REF_VALUE(cmds_zv, &cmds_list);
	TVG_REF_LONG(cmds_cnt_zv, cmds_cnt);
	ZEND_TRY_ASSIGN_REF_VALUE(pts_zv, &pts_list);
	TVG_REF_LONG(pts_cnt_zv, pts_cnt);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_width)
{
	zval *paint_zv;
	double width;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(width)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_stroke_width(paint, (float) width));
}

ZEND_FUNCTION(tvg_shape_get_stroke_width)
{
	zval *paint_zv, *width_zv;
	Tvg_Paint paint;
	float width = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(width_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_width(paint, &width);
	TVG_REF_DOUBLE(width_zv, width);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_color)
{
	zval *paint_zv;
	zend_long r, g, b, a;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_rgba_args(r, g, b, a, 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_stroke_color(paint, (uint8_t) r, (uint8_t) g, (uint8_t) b, (uint8_t) a));
}

ZEND_FUNCTION(tvg_shape_get_stroke_color)
{
	zval *paint_zv, *r_zv, *g_zv, *b_zv, *a_zv;
	Tvg_Paint paint;
	uint8_t r = 0, g = 0, b = 0, a = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(r_zv)
		Z_PARAM_ZVAL(g_zv)
		Z_PARAM_ZVAL(b_zv)
		Z_PARAM_ZVAL(a_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_color(paint, &r, &g, &b, &a);
	TVG_REF_LONG(r_zv, r);
	TVG_REF_LONG(g_zv, g);
	TVG_REF_LONG(b_zv, b);
	TVG_REF_LONG(a_zv, a);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_gradient)
{
	zval *paint_zv, *grad_zv;
	Tvg_Paint paint;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL || !tvg_gradient_can_attach(grad_zv, 2)) {
		RETURN_THROWS();
	}
	result = tvg_shape_set_stroke_gradient(paint, (Tvg_Gradient) tvg_handle_from(Z_OBJ_P(grad_zv))->ptr);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_gradient_attached(grad_zv);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_get_stroke_gradient)
{
	zval *paint_zv, *grad_zv, gradient;
	Tvg_Paint paint;
	Tvg_Gradient grad = NULL;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(grad_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_gradient(paint, &grad);
	tvg_gradient_wrap(result == TVG_RESULT_SUCCESS ? grad : NULL, paint, &gradient);
	ZEND_TRY_ASSIGN_REF_VALUE(grad_zv, &gradient);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_dash)
{
	zval *paint_zv;
	HashTable *dash_ht = NULL;
	zend_long cnt;
	double offset;
	Tvg_Paint paint;
	float *dash;
	bool ok;
	zend_long i;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ARRAY_HT_OR_NULL(dash_ht)
		Z_PARAM_LONG(cnt)
		Z_PARAM_DOUBLE(offset)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_list_count(dash_ht, cnt, 3)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	dash = tvg_floats_read(dash_ht, cnt, 2, &ok);
	if (!ok) {
		RETURN_THROWS();
	}
	for (i = 0; i < cnt; i++) {
		if (!zend_finite(dash[i]) || dash[i] < 0.0f) {
			/* A negative or NaN length never advances ThorVG's dasher. */
			efree(dash);
			zend_argument_value_error(2, "must hold finite, non-negative lengths");
			RETURN_THROWS();
		}
	}
	result = tvg_shape_set_stroke_dash(paint, dash, (uint32_t) cnt, (float) offset);
	if (dash != NULL) {
		efree(dash);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_get_stroke_dash)
{
	zval *paint_zv, *dash_zv, *cnt_zv, *offset_zv, list;
	Tvg_Paint paint;
	const float *dash = NULL;
	uint32_t cnt = 0, i;
	float offset = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(dash_zv)
		Z_PARAM_ZVAL(cnt_zv)
		Z_PARAM_ZVAL(offset_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_dash(paint, &dash, &cnt, &offset);
	if (result != TVG_RESULT_SUCCESS || dash == NULL) {
		cnt = 0;
	}
	array_init_size(&list, cnt);
	for (i = 0; i < cnt; i++) {
		add_next_index_double(&list, (double) dash[i]);
	}
	ZEND_TRY_ASSIGN_REF_VALUE(dash_zv, &list);
	TVG_REF_LONG(cnt_zv, cnt);
	TVG_REF_DOUBLE(offset_zv, offset);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_cap)
{
	zval *paint_zv;
	zend_long cap;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(cap)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(cap, TVG_STROKE_CAP_BUTT, TVG_STROKE_CAP_SQUARE, "a TVG_STROKE_CAP_* value", 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_stroke_cap(paint, (Tvg_Stroke_Cap) cap));
}

ZEND_FUNCTION(tvg_shape_get_stroke_cap)
{
	zval *paint_zv, *cap_zv;
	Tvg_Paint paint;
	Tvg_Stroke_Cap cap = TVG_STROKE_CAP_BUTT;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(cap_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_cap(paint, &cap);
	TVG_REF_LONG(cap_zv, cap);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_join)
{
	zval *paint_zv;
	zend_long join;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(join)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(join, TVG_STROKE_JOIN_MITER, TVG_STROKE_JOIN_BEVEL, "a TVG_STROKE_JOIN_* value", 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_stroke_join(paint, (Tvg_Stroke_Join) join));
}

ZEND_FUNCTION(tvg_shape_get_stroke_join)
{
	zval *paint_zv, *join_zv;
	Tvg_Paint paint;
	Tvg_Stroke_Join join = TVG_STROKE_JOIN_MITER;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(join_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_join(paint, &join);
	TVG_REF_LONG(join_zv, join);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_stroke_miterlimit)
{
	zval *paint_zv;
	double limit;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(limit)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_stroke_miterlimit(paint, (float) limit));
}

ZEND_FUNCTION(tvg_shape_get_stroke_miterlimit)
{
	zval *paint_zv, *limit_zv;
	Tvg_Paint paint;
	float limit = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(limit_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_stroke_miterlimit(paint, &limit);
	TVG_REF_DOUBLE(limit_zv, limit);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_trimpath)
{
	zval *paint_zv;
	double begin, end;
	bool simultaneous;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_DOUBLE(begin)
		Z_PARAM_DOUBLE(end)
		Z_PARAM_BOOL(simultaneous)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_trimpath(paint, (float) begin, (float) end, simultaneous));
}

ZEND_FUNCTION(tvg_shape_set_fill_color)
{
	zval *paint_zv;
	zend_long r, g, b, a;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_rgba_args(r, g, b, a, 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_fill_color(paint, (uint8_t) r, (uint8_t) g, (uint8_t) b, (uint8_t) a));
}

ZEND_FUNCTION(tvg_shape_get_fill_color)
{
	zval *paint_zv, *r_zv, *g_zv, *b_zv, *a_zv;
	Tvg_Paint paint;
	uint8_t r = 0, g = 0, b = 0, a = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(r_zv)
		Z_PARAM_ZVAL(g_zv)
		Z_PARAM_ZVAL(b_zv)
		Z_PARAM_ZVAL(a_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_fill_color(paint, &r, &g, &b, &a);
	TVG_REF_LONG(r_zv, r);
	TVG_REF_LONG(g_zv, g);
	TVG_REF_LONG(b_zv, b);
	TVG_REF_LONG(a_zv, a);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_fill_rule)
{
	zval *paint_zv;
	zend_long rule;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_LONG(rule)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(rule, TVG_FILL_RULE_NON_ZERO, TVG_FILL_RULE_EVEN_ODD, "a TVG_FILL_RULE_* value", 2)) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_fill_rule(paint, (Tvg_Fill_Rule) rule));
}

ZEND_FUNCTION(tvg_shape_get_fill_rule)
{
	zval *paint_zv, *rule_zv;
	Tvg_Paint paint;
	Tvg_Fill_Rule rule = TVG_FILL_RULE_NON_ZERO;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(rule_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_fill_rule(paint, &rule);
	TVG_REF_LONG(rule_zv, rule);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_set_paint_order)
{
	zval *paint_zv;
	bool stroke_first;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_BOOL(stroke_first)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_shape_set_paint_order(paint, stroke_first));
}

ZEND_FUNCTION(tvg_shape_set_gradient)
{
	zval *paint_zv, *grad_zv;
	Tvg_Paint paint;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL || !tvg_gradient_can_attach(grad_zv, 2)) {
		RETURN_THROWS();
	}
	result = tvg_shape_set_gradient(paint, (Tvg_Gradient) tvg_handle_from(Z_OBJ_P(grad_zv))->ptr);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_gradient_attached(grad_zv);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_shape_get_gradient)
{
	zval *paint_zv, *grad_zv, gradient;
	Tvg_Paint paint;
	Tvg_Gradient grad = NULL;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(grad_zv)
	ZEND_PARSE_PARAMETERS_END();

	paint = tvg_paint_arg(paint_zv, TVG_TYPE_SHAPE, 1);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	result = tvg_shape_get_gradient(paint, &grad);
	tvg_gradient_wrap(result == TVG_RESULT_SUCCESS ? grad : NULL, paint, &gradient);
	ZEND_TRY_ASSIGN_REF_VALUE(grad_zv, &gradient);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

void tvg_shape_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
