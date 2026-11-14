/*
 * Gradient bindings (thorvg_gradient.stub.php). Ownership rules: runtime.h, tvg_gradient_arg().
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_gradient_arginfo.h"

#define GRADIENT_CE tvg_handle_ce[TVG_K_GRADIENT]

/* A gradient argument of `type` (linear, radial, conic): ThorVG casts it unchecked. */
static Tvg_Gradient tvg_typed_gradient_arg(zval *zv, Tvg_Type type, const char *what, uint32_t arg_num)
{
	Tvg_Gradient grad = tvg_gradient_arg(zv, arg_num);
	Tvg_Type actual = TVG_TYPE_UNDEF;

	if (grad == NULL) {
		return NULL;
	}
	tvg_gradient_get_type(grad, &actual);
	if (actual != type) {
		zend_argument_type_error(arg_num, "must be a %s gradient", what);
		return NULL;
	}
	return grad;
}

ZEND_FUNCTION(tvg_linear_gradient_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_gradient_wrap(tvg_linear_gradient_new(), NULL, return_value);
}

ZEND_FUNCTION(tvg_radial_gradient_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_gradient_wrap(tvg_radial_gradient_new(), NULL, return_value);
}

ZEND_FUNCTION(tvg_conic_gradient_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_gradient_wrap(tvg_conic_gradient_new(), NULL, return_value);
}

ZEND_FUNCTION(tvg_linear_gradient_set)
{
	zval *grad_zv;
	double x1, y1, x2, y2;
	Tvg_Gradient grad;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_DOUBLE(x1)
		Z_PARAM_DOUBLE(y1)
		Z_PARAM_DOUBLE(x2)
		Z_PARAM_DOUBLE(y2)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_LINEAR_GRAD, "linear", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_linear_gradient_set(grad, (float) x1, (float) y1, (float) x2, (float) y2));
}

ZEND_FUNCTION(tvg_linear_gradient_get)
{
	zval *grad_zv, *x1_zv, *y1_zv, *x2_zv, *y2_zv;
	Tvg_Gradient grad;
	float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(x1_zv)
		Z_PARAM_ZVAL(y1_zv)
		Z_PARAM_ZVAL(x2_zv)
		Z_PARAM_ZVAL(y2_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_LINEAR_GRAD, "linear", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_linear_gradient_get(grad, &x1, &y1, &x2, &y2);
	TVG_REF_DOUBLE(x1_zv, x1);
	TVG_REF_DOUBLE(y1_zv, y1);
	TVG_REF_DOUBLE(x2_zv, x2);
	TVG_REF_DOUBLE(y2_zv, y2);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_radial_gradient_set)
{
	zval *grad_zv;
	double cx, cy, r, fx, fy, fr;
	Tvg_Gradient grad;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_DOUBLE(cx)
		Z_PARAM_DOUBLE(cy)
		Z_PARAM_DOUBLE(r)
		Z_PARAM_DOUBLE(fx)
		Z_PARAM_DOUBLE(fy)
		Z_PARAM_DOUBLE(fr)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_RADIAL_GRAD, "radial", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_radial_gradient_set(grad, (float) cx, (float) cy, (float) r, (float) fx, (float) fy, (float) fr));
}

ZEND_FUNCTION(tvg_radial_gradient_get)
{
	zval *grad_zv, *cx_zv, *cy_zv, *r_zv, *fx_zv, *fy_zv, *fr_zv;
	Tvg_Gradient grad;
	float cx = 0, cy = 0, r = 0, fx = 0, fy = 0, fr = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(cx_zv)
		Z_PARAM_ZVAL(cy_zv)
		Z_PARAM_ZVAL(r_zv)
		Z_PARAM_ZVAL(fx_zv)
		Z_PARAM_ZVAL(fy_zv)
		Z_PARAM_ZVAL(fr_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_RADIAL_GRAD, "radial", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_radial_gradient_get(grad, &cx, &cy, &r, &fx, &fy, &fr);
	TVG_REF_DOUBLE(cx_zv, cx);
	TVG_REF_DOUBLE(cy_zv, cy);
	TVG_REF_DOUBLE(r_zv, r);
	TVG_REF_DOUBLE(fx_zv, fx);
	TVG_REF_DOUBLE(fy_zv, fy);
	TVG_REF_DOUBLE(fr_zv, fr);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_conic_gradient_set)
{
	zval *grad_zv;
	double cx, cy, angle;
	Tvg_Gradient grad;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_DOUBLE(cx)
		Z_PARAM_DOUBLE(cy)
		Z_PARAM_DOUBLE(angle)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_CONIC_GRAD, "conic", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_conic_gradient_set(grad, (float) cx, (float) cy, (float) angle));
}

ZEND_FUNCTION(tvg_conic_gradient_get)
{
	zval *grad_zv, *cx_zv, *cy_zv, *angle_zv;
	Tvg_Gradient grad;
	float cx = 0, cy = 0, angle = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(cx_zv)
		Z_PARAM_ZVAL(cy_zv)
		Z_PARAM_ZVAL(angle_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_typed_gradient_arg(grad_zv, TVG_TYPE_CONIC_GRAD, "conic", 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_conic_gradient_get(grad, &cx, &cy, &angle);
	TVG_REF_DOUBLE(cx_zv, cx);
	TVG_REF_DOUBLE(cy_zv, cy);
	TVG_REF_DOUBLE(angle_zv, angle);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_set_color_stops)
{
	zval *grad_zv;
	HashTable *stops_ht;
	zend_long cnt;
	Tvg_Gradient grad;
	Tvg_Color_Stop *stops;
	bool ok;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ARRAY_HT(stops_ht)
		Z_PARAM_LONG(cnt)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_list_count(stops_ht, cnt, 3)) {
		RETURN_THROWS();
	}
	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	stops = tvg_stops_read(stops_ht, cnt, 2, &ok);
	if (!ok) {
		RETURN_THROWS();
	}
	result = tvg_gradient_set_color_stops(grad, stops, (uint32_t) cnt);
	if (stops != NULL) {
		efree(stops);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_get_color_stops)
{
	zval *grad_zv, *stops_zv, *cnt_zv, list;
	Tvg_Gradient grad;
	const Tvg_Color_Stop *stops = NULL;
	uint32_t cnt = 0, i;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(stops_zv)
		Z_PARAM_ZVAL(cnt_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_gradient_get_color_stops(grad, &stops, &cnt);
	if (result != TVG_RESULT_SUCCESS || stops == NULL) {
		cnt = 0;
	}
	array_init_size(&list, cnt);
	for (i = 0; i < cnt; i++) {
		zval stop;
		tvg_color_stop_new(&stops[i], &stop);
		zend_hash_next_index_insert_new(Z_ARRVAL(list), &stop);
	}
	ZEND_TRY_ASSIGN_REF_VALUE(stops_zv, &list);
	TVG_REF_LONG(cnt_zv, cnt);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_set_spread)
{
	zval *grad_zv;
	zend_long spread;
	Tvg_Gradient grad;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_LONG(spread)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(spread, TVG_STROKE_FILL_PAD, TVG_STROKE_FILL_REPEAT, "a TVG_STROKE_FILL_* value", 2)) {
		RETURN_THROWS();
	}
	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_gradient_set_spread(grad, (Tvg_Stroke_Fill) spread));
}

ZEND_FUNCTION(tvg_gradient_get_spread)
{
	zval *grad_zv, *spread_zv;
	Tvg_Gradient grad;
	Tvg_Stroke_Fill spread = TVG_STROKE_FILL_PAD;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(spread_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_gradient_get_spread(grad, &spread);
	TVG_REF_LONG(spread_zv, spread);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_set_transform)
{
	zval *grad_zv;
	zend_object *m_obj;
	Tvg_Gradient grad;
	Tvg_Matrix m;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_OBJ_OF_CLASS(m_obj, tvg_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	tvg_matrix_read(m_obj, &m);
	RETURN_LONG((zend_long) tvg_gradient_set_transform(grad, &m));
}

ZEND_FUNCTION(tvg_gradient_get_transform)
{
	zval *grad_zv;
	zend_object *m_obj;
	Tvg_Gradient grad;
	Tvg_Matrix m;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_OBJ_OF_CLASS(m_obj, tvg_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	memset(&m, 0, sizeof(m));
	result = tvg_gradient_get_transform(grad, &m);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_matrix_write(m_obj, &m);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_get_type)
{
	zval *grad_zv, *type_zv;
	Tvg_Gradient grad;
	Tvg_Type type = TVG_TYPE_UNDEF;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
		Z_PARAM_ZVAL(type_zv)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	result = tvg_gradient_get_type(grad, &type);
	TVG_REF_LONG(type_zv, type);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_gradient_duplicate)
{
	zval *grad_zv;
	Tvg_Gradient grad;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	tvg_gradient_wrap(tvg_gradient_duplicate(grad), NULL, return_value);
}

ZEND_FUNCTION(tvg_gradient_del)
{
	zval *grad_zv;
	Tvg_Gradient grad;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
	ZEND_PARSE_PARAMETERS_END();

	grad = tvg_gradient_arg(grad_zv, 1);
	if (grad == NULL) {
		RETURN_THROWS();
	}
	if (tvg_handle_from(Z_OBJ_P(grad_zv))->owner != NULL) {
		zend_argument_value_error(1, "belongs to a shape, which deletes it");
		RETURN_THROWS();
	}
	tvg_handle_release(Z_OBJ_P(grad_zv));
	result = tvg_gradient_del(grad);
	RETURN_LONG((zend_long) result);
}

void tvg_gradient_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
