/*
 * Picture, scene, text and font bindings (thorvg_picture.stub.php). Every paint
 * function checks its paint's type: ThorVG casts it unchecked.
 */

#ifdef HAVE_CONFIG_H
#include <inttypes.h>
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_picture_arginfo.h"

#define PAINT_CE tvg_handle_ce[TVG_K_PAINT]
#define GRADIENT_CE tvg_handle_ce[TVG_K_GRADIENT]

/* ---- picture ---- */

ZEND_FUNCTION(tvg_picture_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_paint_wrap(tvg_picture_new(), return_value);
}

ZEND_FUNCTION(tvg_picture_load)
{
	zval *picture_zv;
	char *path;
	size_t path_len;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_PATH(path, path_len)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_path_utf8(path, path_len, 2)) {
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	if (!tvg_path_allowed(path)) {
		RETURN_LONG((zend_long) TVG_RESULT_INVALID_ARGUMENT);
	}
	RETURN_LONG((zend_long) tvg_picture_load(picture, path));
}

/* The Tvg_Colorspace values a picture can be loaded from. */
static bool tvg_raw_colorspace_arg(zend_long cs, uint32_t arg_num)
{
	if ((cs >= TVG_COLORSPACE_ABGR8888 && cs <= TVG_COLORSPACE_XRGB8888) || cs == TVG_COLORSPACE_UNKNOWN) {
		return true;
	}
	zend_argument_value_error(arg_num, "must be a TVG_COLORSPACE_* value");
	return false;
}

ZEND_FUNCTION(tvg_picture_load_raw)
{
	zval *picture_zv;
	zend_string *data = NULL;
	zend_long address = 0, w, h, cs;
	bool copy;
	Tvg_Paint picture;
	const void *bytes;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_STR_OR_LONG(data, address)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
		Z_PARAM_LONG(cs)
		Z_PARAM_BOOL(copy)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(w, 3) || !tvg_u32(h, 4) || !tvg_raw_colorspace_arg(cs, 5)) {
		RETURN_THROWS();
	}
	if (!tvg_memory_arg(data, address, (size_t) w * (size_t) h * 4, 2, &bytes)) {
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	result = tvg_picture_load_raw(picture, (const uint32_t *) bytes, (uint32_t) w, (uint32_t) h, (Tvg_Colorspace) cs, copy);
	if (result == TVG_RESULT_SUCCESS && !copy && data != NULL) {
		tvg_borrow(data);
	}
	RETURN_LONG((zend_long) result);
}

/*
 * Binding addition, the counterpart of tvg_swcanvas_get_alpha(): one coverage byte per pixel loaded
 * as a raw ARGB8888 picture of 0xCC000000 words (black at alpha c), copied by ThorVG. An A8 mask
 * becomes an alpha-mask picture in C rather than by widening every byte in PHP.
 */
ZEND_FUNCTION(tvg_picture_load_alpha)
{
	zval *picture_zv;
	zend_string *alpha;
	zend_long w, h;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_STR(alpha)
		Z_PARAM_LONG(w)
		Z_PARAM_LONG(h)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(w, 3) || !tvg_u32(h, 4)) {
		RETURN_THROWS();
	}
	if ((uint64_t) w * (uint64_t) h != ZSTR_LEN(alpha)) {
		zend_argument_value_error(2, "must hold w * h bytes (%" PRIu64 "), %zu given", (uint64_t) w * (uint64_t) h, ZSTR_LEN(alpha));
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	size_t n = ZSTR_LEN(alpha);
	uint32_t *words = safe_emalloc(n ? n : 1, sizeof(uint32_t), 0);
	const unsigned char *in = (const unsigned char *) ZSTR_VAL(alpha);
	for (size_t i = 0; i < n; i++) {
		words[i] = (uint32_t) in[i] << 24;
	}
	Tvg_Result result = tvg_picture_load_raw(picture, words, (uint32_t) w, (uint32_t) h, TVG_COLORSPACE_ARGB8888, true);
	efree(words);
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_picture_load_data)
{
	zval *picture_zv;
	zend_string *data = NULL, *mimetype = NULL, *rpath = NULL;
	zend_long address = 0, size;
	bool copy;
	Tvg_Paint picture;
	const void *bytes;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_STR_OR_LONG(data, address)
		Z_PARAM_LONG(size)
		Z_PARAM_STR_OR_NULL(mimetype)
		Z_PARAM_PATH_STR_OR_NULL(rpath)
		Z_PARAM_BOOL(copy)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(size, 3)) {
		RETURN_THROWS();
	}
	if (!tvg_memory_arg(data, address, (size_t) size, 2, &bytes)) {
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	if (rpath != NULL && !tvg_path_allowed(ZSTR_VAL(rpath))) {
		RETURN_LONG((zend_long) TVG_RESULT_INVALID_ARGUMENT);
	}
	result = tvg_picture_load_data(picture, (const char *) bytes, (uint32_t) size,
		mimetype != NULL ? ZSTR_VAL(mimetype) : NULL, rpath != NULL ? ZSTR_VAL(rpath) : NULL, copy);
	if (result == TVG_RESULT_SUCCESS && !copy && data != NULL) {
		tvg_borrow(data);
	}
	RETURN_LONG((zend_long) result);
}

/* ThorVG's asset resolver: only the Lottie loader calls it, on the loading thread. */
static bool tvg_asset_resolver_trampoline(Tvg_Paint paint, const char *src, void *data)
{
	zval args[3], retval;
	bool answer = false;

	tvg_paint_wrap(paint, &args[0]);
	ZVAL_STRING(&args[1], src != NULL ? src : "");
	ZVAL_COPY(&args[2], &((tvg_callback *) data)->data);
	if (tvg_callback_call((tvg_callback *) data, args, 3, &retval)) {
		answer = zend_is_true(&retval);
		zval_ptr_dtor(&retval);
	}
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	zval_ptr_dtor(&args[2]);
	return answer;
}

ZEND_FUNCTION(tvg_picture_set_asset_resolver)
{
	zval *picture_zv, *resolver = NULL, *data;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_ZVAL(resolver)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();

	if (Z_TYPE_P(resolver) != IS_NULL && !zend_is_callable(resolver, 0, NULL)) {
		zend_argument_type_error(2, "must be a valid callback or null");
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	if (Z_TYPE_P(resolver) == IS_NULL) {
		RETURN_LONG((zend_long) tvg_picture_set_asset_resolver(picture, NULL, NULL));
	}
	RETURN_LONG((zend_long) tvg_picture_set_asset_resolver(picture, tvg_asset_resolver_trampoline, tvg_callback_new(resolver, data)));
}

ZEND_FUNCTION(tvg_picture_set_size)
{
	zval *picture_zv;
	double w, h;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();

	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_picture_set_size(picture, (float) w, (float) h));
}

ZEND_FUNCTION(tvg_picture_get_size)
{
	zval *picture_zv, *w_zv, *h_zv;
	Tvg_Paint picture;
	float w = 0, h = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_ZVAL(w_zv)
		Z_PARAM_ZVAL(h_zv)
	ZEND_PARSE_PARAMETERS_END();

	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	result = tvg_picture_get_size(picture, &w, &h);
	TVG_REF_DOUBLE(w_zv, w);
	TVG_REF_DOUBLE(h_zv, h);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_picture_set_origin)
{
	zval *picture_zv;
	double x, y;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_picture_set_origin(picture, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_picture_get_origin)
{
	zval *picture_zv, *x_zv, *y_zv;
	Tvg_Paint picture;
	float x = 0, y = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_ZVAL(x_zv)
		Z_PARAM_ZVAL(y_zv)
	ZEND_PARSE_PARAMETERS_END();

	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	result = tvg_picture_get_origin(picture, &x, &y);
	TVG_REF_DOUBLE(x_zv, x);
	TVG_REF_DOUBLE(y_zv, y);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_picture_get_paint)
{
	zval *picture_zv;
	zend_long id;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(id, 2)) {
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_picture_get_paint(picture, (uint32_t) id), return_value);
}

ZEND_FUNCTION(tvg_picture_set_filter)
{
	zval *picture_zv;
	zend_long method;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_LONG(method)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(method, TVG_FILTER_METHOD_BILINEAR, TVG_FILTER_METHOD_NEAREST, "a TVG_FILTER_METHOD_* value", 2)) {
		RETURN_THROWS();
	}
	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_picture_set_filter(picture, (Tvg_Filter_Method) method));
}

ZEND_FUNCTION(tvg_picture_set_accessible)
{
	zval *picture_zv;
	bool accessible;
	Tvg_Paint picture;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(picture_zv, PAINT_CE)
		Z_PARAM_BOOL(accessible)
	ZEND_PARSE_PARAMETERS_END();

	picture = tvg_paint_arg(picture_zv, TVG_TYPE_PICTURE, 1);
	if (picture == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_picture_set_accessible(picture, accessible));
}

/* ---- scene ---- */

ZEND_FUNCTION(tvg_scene_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_paint_wrap(tvg_scene_new(), return_value);
}

ZEND_FUNCTION(tvg_scene_add)
{
	zval *scene_zv, *paint_zv;
	Tvg_Paint scene, paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	if (paint == scene) {
		zend_argument_value_error(2, "must not be the scene itself");
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add(scene, paint));
}

ZEND_FUNCTION(tvg_scene_insert)
{
	zval *scene_zv, *target_zv, *at_zv = NULL;
	Tvg_Paint scene, target, at = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(target_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(at_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	target = tvg_paint_arg(target_zv, TVG_TYPE_UNDEF, 2);
	if (target == NULL) {
		RETURN_THROWS();
	}
	if (at_zv != NULL && (at = tvg_paint_arg(at_zv, TVG_TYPE_UNDEF, 3)) == NULL) {
		RETURN_THROWS();
	}
	if (target == scene) {
		zend_argument_value_error(2, "must not be the scene itself");
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_insert(scene, target, at));
}

ZEND_FUNCTION(tvg_scene_remove)
{
	zval *scene_zv, *paint_zv;
	Tvg_Paint scene, paint;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_remove(scene, paint));
}

ZEND_FUNCTION(tvg_scene_clear_effects)
{
	zval *scene_zv;
	Tvg_Paint scene;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_clear_effects(scene));
}

ZEND_FUNCTION(tvg_scene_add_effect_gaussian_blur)
{
	zval *scene_zv;
	double sigma;
	zend_long direction, border, quality;
	Tvg_Paint scene;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_DOUBLE(sigma)
		Z_PARAM_LONG(direction)
		Z_PARAM_LONG(border)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(direction, INT_MIN, INT_MAX, "an int", 3) || !tvg_range(border, INT_MIN, INT_MAX, "an int", 4)
		|| !tvg_range(quality, INT_MIN, INT_MAX, "an int", 5)) {
		RETURN_THROWS();
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_gaussian_blur(scene, sigma, (int) direction, (int) border, (int) quality));
}

ZEND_FUNCTION(tvg_scene_add_effect_motion_blur)
{
	zval *scene_zv;
	double distance, angle;
	zend_long quality;
	Tvg_Paint scene;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_DOUBLE(distance)
		Z_PARAM_DOUBLE(angle)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(quality, INT_MIN, INT_MAX, "an int", 4)) {
		RETURN_THROWS();
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_motion_blur(scene, distance, angle, (int) quality));
}

ZEND_FUNCTION(tvg_scene_add_effect_drop_shadow)
{
	zval *scene_zv;
	zend_long r, g, b, a, quality;
	double angle, distance, sigma;
	Tvg_Paint scene;

	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
		Z_PARAM_DOUBLE(angle)
		Z_PARAM_DOUBLE(distance)
		Z_PARAM_DOUBLE(sigma)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(r, INT_MIN, INT_MAX, "an int", 2) || !tvg_range(g, INT_MIN, INT_MAX, "an int", 3)
		|| !tvg_range(b, INT_MIN, INT_MAX, "an int", 4) || !tvg_range(a, INT_MIN, INT_MAX, "an int", 5)
		|| !tvg_range(quality, INT_MIN, INT_MAX, "an int", 9)) {
		RETURN_THROWS();
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_drop_shadow(scene, (int) r, (int) g, (int) b, (int) a, angle, distance, sigma, (int) quality));
}

ZEND_FUNCTION(tvg_scene_add_effect_fill)
{
	zval *scene_zv;
	zend_long r, g, b, a;
	Tvg_Paint scene;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(r, INT_MIN, INT_MAX, "an int", 2) || !tvg_range(g, INT_MIN, INT_MAX, "an int", 3)
		|| !tvg_range(b, INT_MIN, INT_MAX, "an int", 4) || !tvg_range(a, INT_MIN, INT_MAX, "an int", 5)) {
		RETURN_THROWS();
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_fill(scene, (int) r, (int) g, (int) b, (int) a));
}

ZEND_FUNCTION(tvg_scene_add_effect_tint)
{
	zval *scene_zv;
	zend_long c[6];
	double intensity;
	Tvg_Paint scene;
	int i;

	ZEND_PARSE_PARAMETERS_START(8, 8)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_LONG(c[0])
		Z_PARAM_LONG(c[1])
		Z_PARAM_LONG(c[2])
		Z_PARAM_LONG(c[3])
		Z_PARAM_LONG(c[4])
		Z_PARAM_LONG(c[5])
		Z_PARAM_DOUBLE(intensity)
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 6; i++) {
		if (!tvg_range(c[i], INT_MIN, INT_MAX, "an int", (uint32_t) i + 2)) {
			RETURN_THROWS();
		}
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_tint(scene, (int) c[0], (int) c[1], (int) c[2], (int) c[3], (int) c[4], (int) c[5], intensity));
}

ZEND_FUNCTION(tvg_scene_add_effect_tritone)
{
	zval *scene_zv;
	zend_long c[10];
	Tvg_Paint scene;
	int i;

	ZEND_PARSE_PARAMETERS_START(11, 11)
		Z_PARAM_OBJECT_OF_CLASS(scene_zv, PAINT_CE)
		Z_PARAM_LONG(c[0])
		Z_PARAM_LONG(c[1])
		Z_PARAM_LONG(c[2])
		Z_PARAM_LONG(c[3])
		Z_PARAM_LONG(c[4])
		Z_PARAM_LONG(c[5])
		Z_PARAM_LONG(c[6])
		Z_PARAM_LONG(c[7])
		Z_PARAM_LONG(c[8])
		Z_PARAM_LONG(c[9])
	ZEND_PARSE_PARAMETERS_END();

	for (i = 0; i < 10; i++) {
		if (!tvg_range(c[i], INT_MIN, INT_MAX, "an int", (uint32_t) i + 2)) {
			RETURN_THROWS();
		}
	}
	scene = tvg_paint_arg(scene_zv, TVG_TYPE_SCENE, 1);
	if (scene == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_scene_add_effect_tritone(scene, (int) c[0], (int) c[1], (int) c[2], (int) c[3], (int) c[4],
		(int) c[5], (int) c[6], (int) c[7], (int) c[8], (int) c[9]));
}

/* ---- text ---- */

ZEND_FUNCTION(tvg_text_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_paint_wrap(tvg_text_new(), return_value);
}

ZEND_FUNCTION(tvg_text_set_font)
{
	zval *text_zv;
	zend_string *name = NULL;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_STR_OR_NULL(name)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_font(text, name != NULL ? ZSTR_VAL(name) : NULL));
}

ZEND_FUNCTION(tvg_text_set_size)
{
	zval *text_zv;
	double size;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(size)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_size(text, (float) size));
}

ZEND_FUNCTION(tvg_text_set_text)
{
	zval *text_zv;
	zend_string *utf8 = NULL;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_STR_OR_NULL(utf8)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_text(text, utf8 != NULL ? ZSTR_VAL(utf8) : NULL));
}

ZEND_FUNCTION(tvg_text_align)
{
	zval *text_zv;
	double x, y;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(x)
		Z_PARAM_DOUBLE(y)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_align(text, (float) x, (float) y));
}

ZEND_FUNCTION(tvg_text_layout)
{
	zval *text_zv;
	double w, h;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(w)
		Z_PARAM_DOUBLE(h)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_layout(text, (float) w, (float) h));
}

ZEND_FUNCTION(tvg_text_wrap_mode)
{
	zval *text_zv;
	zend_long mode;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_range(mode, TVG_TEXT_WRAP_NONE, TVG_TEXT_WRAP_HYPHENATION, "a TVG_TEXT_WRAP_* value", 2)) {
		RETURN_THROWS();
	}
	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_wrap_mode(text, (Tvg_Text_Wrap) mode));
}

ZEND_FUNCTION(tvg_text_line_count)
{
	zval *text_zv;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_line_count(text));
}

ZEND_FUNCTION(tvg_text_spacing)
{
	zval *text_zv;
	double letter, line;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(letter)
		Z_PARAM_DOUBLE(line)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_spacing(text, (float) letter, (float) line));
}

ZEND_FUNCTION(tvg_text_set_italic)
{
	zval *text_zv;
	double shear;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(shear)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_italic(text, (float) shear));
}

ZEND_FUNCTION(tvg_text_set_outline)
{
	zval *text_zv;
	double width;
	zend_long r, g, b;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_DOUBLE(width)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u8(r, 3) || !tvg_u8(g, 4) || !tvg_u8(b, 5)) {
		RETURN_THROWS();
	}
	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_outline(text, (float) width, (uint8_t) r, (uint8_t) g, (uint8_t) b));
}

ZEND_FUNCTION(tvg_text_set_color)
{
	zval *text_zv;
	zend_long r, g, b;
	Tvg_Paint text;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u8(r, 2) || !tvg_u8(g, 3) || !tvg_u8(b, 4)) {
		RETURN_THROWS();
	}
	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_text_set_color(text, (uint8_t) r, (uint8_t) g, (uint8_t) b));
}

ZEND_FUNCTION(tvg_text_set_gradient)
{
	zval *text_zv, *grad_zv;
	Tvg_Paint text;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_OBJECT_OF_CLASS(grad_zv, GRADIENT_CE)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL || !tvg_gradient_can_attach(grad_zv, 2)) {
		RETURN_THROWS();
	}
	result = tvg_text_set_gradient(text, (Tvg_Gradient) tvg_handle_from(Z_OBJ_P(grad_zv))->ptr);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_gradient_attached(grad_zv);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_text_get_text_metrics)
{
	zval *text_zv;
	zend_object *metrics_obj;
	Tvg_Paint text;
	Tvg_Text_Metrics metrics;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_OBJ_OF_CLASS(metrics_obj, tvg_text_metrics_ce)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	memset(&metrics, 0, sizeof(metrics));
	result = tvg_text_get_text_metrics(text, &metrics);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_text_metrics_write(metrics_obj, &metrics);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_text_get_glyph_metrics)
{
	zval *text_zv, *next_zv;
	zend_string *ch;
	zend_object *metrics_obj;
	Tvg_Paint text;
	Tvg_Glyph_Metrics metrics;
	const char *next = NULL;
	Tvg_Result result;
	zend_long offset;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(text_zv, PAINT_CE)
		Z_PARAM_STR(ch)
		Z_PARAM_OBJ_OF_CLASS(metrics_obj, tvg_glyph_metrics_ce)
		Z_PARAM_ZVAL(next_zv)
	ZEND_PARSE_PARAMETERS_END();

	text = tvg_paint_arg(text_zv, TVG_TYPE_TEXT, 1);
	if (text == NULL) {
		RETURN_THROWS();
	}
	memset(&metrics, 0, sizeof(metrics));
	result = tvg_text_get_glyph_metrics(text, ZSTR_VAL(ch), &metrics, &next);
	if (result == TVG_RESULT_SUCCESS) {
		tvg_glyph_metrics_write(metrics_obj, &metrics);
	}
	/* `next` points into $ch (ThorVG stops at its terminating NUL): its byte offset. */
	offset = (next != NULL && next >= ZSTR_VAL(ch) && next <= ZSTR_VAL(ch) + ZSTR_LEN(ch)) ? (zend_long) (next - ZSTR_VAL(ch)) : 0;
	TVG_REF_LONG(next_zv, offset);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

/* ---- font ---- */

ZEND_FUNCTION(tvg_font_load)
{
	char *path;
	size_t path_len;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH(path, path_len)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_path_utf8(path, path_len, 1)) {
		RETURN_THROWS();
	}
	if (!tvg_path_allowed(path)) {
		RETURN_LONG((zend_long) TVG_RESULT_INVALID_ARGUMENT);
	}
	RETURN_LONG((zend_long) tvg_font_load(path));
}

ZEND_FUNCTION(tvg_font_load_data)
{
	zend_string *name, *data = NULL, *mimetype = NULL;
	zend_long address = 0, size;
	bool copy;
	const void *bytes;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_STR(name)
		Z_PARAM_STR_OR_LONG(data, address)
		Z_PARAM_LONG(size)
		Z_PARAM_STR_OR_NULL(mimetype)
		Z_PARAM_BOOL(copy)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(size, 3)) {
		RETURN_THROWS();
	}
	if (!tvg_memory_arg(data, address, (size_t) size, 2, &bytes)) {
		RETURN_THROWS();
	}
	result = tvg_font_load_data(ZSTR_VAL(name), (const char *) bytes, (uint32_t) size, mimetype != NULL ? ZSTR_VAL(mimetype) : NULL, copy);
	if (result == TVG_RESULT_SUCCESS && !copy && data != NULL) {
		/* ThorVG's font table outlives the request: the font goes when the string does. */
		tvg_borrow(data);
		tvg_borrow_font(ZSTR_VAL(name));
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_font_unload)
{
	zend_string *path;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(path)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) tvg_font_unload(ZSTR_VAL(path)));
}

void tvg_picture_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
