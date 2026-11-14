/*
 * Saver, animation, accessor, Lottie and video bindings (thorvg_misc.stub.php). This build
 * has no Lottie loader: its functions answer what ThorVG answers without it.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "runtime.h"
#include "../stubs/thorvg_misc_arginfo.h"

#define PAINT_CE tvg_handle_ce[TVG_K_PAINT]
#define SAVER_CE tvg_handle_ce[TVG_K_SAVER]
#define ANIMATION_CE tvg_handle_ce[TVG_K_ANIMATION]
#define ACCESSOR_CE tvg_handle_ce[TVG_K_ACCESSOR]
#define VIDEO_CE tvg_handle_ce[TVG_K_VIDEO]

static Tvg_Saver tvg_saver_arg(zval *zv, uint32_t n) { return (Tvg_Saver) tvg_handle_arg(zv, TVG_K_SAVER, n); }
static Tvg_Animation tvg_animation_arg(zval *zv, uint32_t n) { return (Tvg_Animation) tvg_handle_arg(zv, TVG_K_ANIMATION, n); }
static Tvg_Accessor tvg_accessor_arg(zval *zv, uint32_t n) { return (Tvg_Accessor) tvg_handle_arg(zv, TVG_K_ACCESSOR, n); }
static Tvg_Video tvg_video_arg(zval *zv, uint32_t n) { return (Tvg_Video) tvg_handle_arg(zv, TVG_K_VIDEO, n); }

/* Drops what a saver keeps for its save in progress. */
static void tvg_saver_forget(zval *saver_zv)
{
	tvg_handle_obj *handle = tvg_handle_from(Z_OBJ_P(saver_zv));

	zval_ptr_dtor(&handle->keep);
	ZVAL_UNDEF(&handle->keep);
}

/* ---- saver ---- */

ZEND_FUNCTION(tvg_saver_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_handle_new(TVG_K_SAVER, tvg_saver_new(), return_value);
}

ZEND_FUNCTION(tvg_saver_save_paint)
{
	zval *saver_zv, *paint_zv;
	char *path;
	size_t path_len;
	zend_long quality;
	Tvg_Saver saver;
	Tvg_Paint paint;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(saver_zv, SAVER_CE)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_PATH(path, path_len)
		Z_PARAM_LONG(quality)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(quality, 4)) {
		RETURN_THROWS();
	}
	saver = tvg_saver_arg(saver_zv, 1);
	if (saver == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	if (!tvg_path_allowed(path)) {
		RETURN_LONG((zend_long) TVG_RESULT_INVALID_ARGUMENT);
	}
	/* ThorVG releases the paint only when nothing references it; the object's reference stays. */
	RETURN_LONG((zend_long) tvg_saver_save_paint(saver, paint, path, (uint32_t) quality));
}

ZEND_FUNCTION(tvg_saver_save_animation)
{
	zval *saver_zv, *animation_zv;
	char *path;
	size_t path_len;
	zend_long quality, fps;
	Tvg_Saver saver;
	Tvg_Animation animation;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(saver_zv, SAVER_CE)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_PATH(path, path_len)
		Z_PARAM_LONG(quality)
		Z_PARAM_LONG(fps)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(quality, 4) || !tvg_u32(fps, 5)) {
		RETURN_THROWS();
	}
	saver = tvg_saver_arg(saver_zv, 1);
	if (saver == NULL) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 2);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	if (!tvg_path_allowed(path)) {
		RETURN_LONG((zend_long) TVG_RESULT_INVALID_ARGUMENT);
	}
	/* The object holds a reference on the animation's picture, so ThorVG never deletes the animation here. */
	result = tvg_saver_save_animation(saver, animation, path, (uint32_t) quality, (uint32_t) fps);
	if (result == TVG_RESULT_SUCCESS) {
		/* The GIF saver renders the animation on a worker thread until sync: keep it alive. */
		tvg_saver_forget(saver_zv);
		ZVAL_COPY(&tvg_handle_from(Z_OBJ_P(saver_zv))->keep, animation_zv);
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_saver_sync)
{
	zval *saver_zv;
	Tvg_Saver saver;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(saver_zv, SAVER_CE)
	ZEND_PARSE_PARAMETERS_END();

	saver = tvg_saver_arg(saver_zv, 1);
	if (saver == NULL) {
		RETURN_THROWS();
	}
	result = tvg_saver_sync(saver);
	tvg_saver_forget(saver_zv);
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_saver_del)
{
	zval *saver_zv;
	Tvg_Saver saver;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(saver_zv, SAVER_CE)
	ZEND_PARSE_PARAMETERS_END();

	saver = tvg_saver_arg(saver_zv, 1);
	if (saver == NULL) {
		RETURN_THROWS();
	}
	/* Finish a save in progress before the saver and what it keeps go. */
	tvg_saver_sync(saver);
	result = tvg_saver_del(saver);
	tvg_handle_release(Z_OBJ_P(saver_zv));
	tvg_saver_forget(saver_zv);
	RETURN_LONG((zend_long) result);
}

/* ---- animation ---- */

ZEND_FUNCTION(tvg_animation_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_handle_new(TVG_K_ANIMATION, tvg_animation_new(), return_value);
}

ZEND_FUNCTION(tvg_animation_set_frame)
{
	zval *animation_zv;
	double no;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(no)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_animation_set_frame(animation, (float) no));
}

ZEND_FUNCTION(tvg_animation_get_picture)
{
	zval *animation_zv;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_animation_get_picture(animation), return_value);
}

ZEND_FUNCTION(tvg_animation_get_frame)
{
	zval *animation_zv, *no_zv;
	Tvg_Animation animation;
	float no = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(no_zv)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_animation_get_frame(animation, &no);
	TVG_REF_DOUBLE(no_zv, no);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_animation_get_total_frame)
{
	zval *animation_zv, *cnt_zv;
	Tvg_Animation animation;
	float cnt = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(cnt_zv)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_animation_get_total_frame(animation, &cnt);
	TVG_REF_DOUBLE(cnt_zv, cnt);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_animation_get_duration)
{
	zval *animation_zv, *duration_zv;
	Tvg_Animation animation;
	float duration = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(duration_zv)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_animation_get_duration(animation, &duration);
	TVG_REF_DOUBLE(duration_zv, duration);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_animation_set_segment)
{
	zval *animation_zv;
	double begin, end;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(begin)
		Z_PARAM_DOUBLE(end)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_animation_set_segment(animation, (float) begin, (float) end));
}

ZEND_FUNCTION(tvg_animation_get_segment)
{
	zval *animation_zv, *begin_zv, *end_zv;
	Tvg_Animation animation;
	float begin = 0, end = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(begin_zv)
		Z_PARAM_ZVAL(end_zv)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_animation_get_segment(animation, &begin, &end);
	TVG_REF_DOUBLE(begin_zv, begin);
	TVG_REF_DOUBLE(end_zv, end);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_animation_del)
{
	zval *animation_zv;
	Tvg_Animation animation;
	tvg_handle_obj *handle;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	handle = tvg_handle_from(Z_OBJ_P(animation_zv));
	if (handle->picture != NULL) {
		tvg_paint_unref(handle->picture, false);
		handle->picture = NULL;
	}
	tvg_handle_release(Z_OBJ_P(animation_zv));
	RETURN_LONG((zend_long) tvg_animation_del(animation));
}

/* ---- accessor ---- */

ZEND_FUNCTION(tvg_accessor_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_handle_new(TVG_K_ACCESSOR, tvg_accessor_new(), return_value);
}

ZEND_FUNCTION(tvg_accessor_del)
{
	zval *accessor_zv;
	Tvg_Accessor accessor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(accessor_zv, ACCESSOR_CE)
	ZEND_PARSE_PARAMETERS_END();

	accessor = tvg_accessor_arg(accessor_zv, 1);
	if (accessor == NULL) {
		RETURN_THROWS();
	}
	tvg_handle_release(Z_OBJ_P(accessor_zv));
	RETURN_LONG((zend_long) tvg_accessor_del(accessor));
}

/* The accessor's walk, synchronous: an exception stops it. */
static bool tvg_accessor_trampoline(Tvg_Paint paint, void *data)
{
	zval args[2], retval;
	bool go_on = false;

	tvg_paint_wrap(paint, &args[0]);
	ZVAL_COPY(&args[1], &((tvg_callback *) data)->data);
	if (tvg_callback_call((tvg_callback *) data, args, 2, &retval)) {
		go_on = zend_is_true(&retval);
		zval_ptr_dtor(&retval);
	}
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	return go_on;
}

ZEND_FUNCTION(tvg_accessor_set)
{
	zval *accessor_zv, *paint_zv, *func, *data;
	Tvg_Accessor accessor;
	Tvg_Paint paint;
	tvg_callback cb;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(accessor_zv, ACCESSOR_CE)
		Z_PARAM_OBJECT_OF_CLASS(paint_zv, PAINT_CE)
		Z_PARAM_ZVAL(func)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();

	if (!zend_is_callable(func, 0, NULL)) {
		zend_argument_type_error(3, "must be a valid callback");
		RETURN_THROWS();
	}
	accessor = tvg_accessor_arg(accessor_zv, 1);
	if (accessor == NULL) {
		RETURN_THROWS();
	}
	paint = tvg_paint_arg(paint_zv, TVG_TYPE_UNDEF, 2);
	if (paint == NULL) {
		RETURN_THROWS();
	}
	/* Called only during this call: the record lives on the stack. */
	ZVAL_COPY_VALUE(&cb.callable, func);
	ZVAL_COPY_VALUE(&cb.data, data);
	cb.thread = pthread_self();
	result = tvg_accessor_set(accessor, paint, tvg_accessor_trampoline, &cb);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_accessor_generate_id)
{
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG((zend_long) tvg_accessor_generate_id(ZSTR_VAL(name)));
}

ZEND_FUNCTION(tvg_accessor_get_name)
{
	zval *accessor_zv;
	zend_long id;
	Tvg_Accessor accessor;
	const char *name;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(accessor_zv, ACCESSOR_CE)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(id, 2)) {
		RETURN_THROWS();
	}
	accessor = tvg_accessor_arg(accessor_zv, 1);
	if (accessor == NULL) {
		RETURN_THROWS();
	}
	name = tvg_accessor_get_name(accessor, (uint32_t) id);
	if (name == NULL) {
		RETURN_NULL();
	}
	RETURN_STRING(name);
}

/* ---- Lottie (no loader in this build) ---- */

ZEND_FUNCTION(tvg_lottie_animation_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_handle_new(TVG_K_ANIMATION, tvg_lottie_animation_new(), return_value);
}

ZEND_FUNCTION(tvg_lottie_animation_gen_slot)
{
	zval *animation_zv;
	zend_string *slot;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_STR(slot)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_gen_slot(animation, ZSTR_VAL(slot)));
}

ZEND_FUNCTION(tvg_lottie_animation_apply_slot)
{
	zval *animation_zv;
	zend_long id;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(id, 2)) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_apply_slot(animation, (uint32_t) id));
}

ZEND_FUNCTION(tvg_lottie_animation_del_slot)
{
	zval *animation_zv;
	zend_long id;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(id, 2)) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_del_slot(animation, (uint32_t) id));
}

ZEND_FUNCTION(tvg_lottie_animation_set_marker)
{
	zval *animation_zv;
	zend_string *marker;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_STR(marker)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_set_marker(animation, ZSTR_VAL(marker)));
}

ZEND_FUNCTION(tvg_lottie_animation_get_markers_cnt)
{
	zval *animation_zv, *cnt_zv;
	Tvg_Animation animation;
	uint32_t cnt = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(cnt_zv)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_lottie_animation_get_markers_cnt(animation, &cnt);
	TVG_REF_LONG(cnt_zv, cnt);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_lottie_animation_get_marker)
{
	zval *animation_zv, *name_zv;
	zend_long idx;
	Tvg_Animation animation;
	const char *name = NULL;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_LONG(idx)
		Z_PARAM_ZVAL(name_zv)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(idx, 2)) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
	result = tvg_lottie_animation_get_marker(animation, (uint32_t) idx, &name);
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
	if (name != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(name_zv, name);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(name_zv);
	}
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_lottie_animation_get_marker_info)
{
	zval *animation_zv, *name_zv, *begin_zv, *end_zv;
	zend_long idx;
	Tvg_Animation animation;
	const char *name = NULL;
	float begin = 0, end = 0;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_LONG(idx)
		Z_PARAM_ZVAL(name_zv)
		Z_PARAM_ZVAL(begin_zv)
		Z_PARAM_ZVAL(end_zv)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u32(idx, 2)) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	result = tvg_lottie_animation_get_marker_info(animation, (uint32_t) idx, &name, &begin, &end);
	if (name != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(name_zv, name);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(name_zv);
	}
	TVG_REF_DOUBLE(begin_zv, begin);
	TVG_REF_DOUBLE(end_zv, end);
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

ZEND_FUNCTION(tvg_lottie_animation_tween)
{
	zval *animation_zv;
	double from, to, progress;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(from)
		Z_PARAM_DOUBLE(to)
		Z_PARAM_DOUBLE(progress)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_tween(animation, (float) from, (float) to, (float) progress));
}

ZEND_FUNCTION(tvg_lottie_animation_tween_to)
{
	zval *animation_zv;
	double to;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(to)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_tween_to(animation, (float) to));
}

ZEND_FUNCTION(tvg_lottie_animation_tween_go)
{
	zval *animation_zv;
	double progress;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(progress)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_tween_go(animation, (float) progress));
}

ZEND_FUNCTION(tvg_lottie_animation_set_quality)
{
	zval *animation_zv;
	zend_long value;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	if (!tvg_u8(value, 2)) {
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_set_quality(animation, (uint8_t) value));
}

ZEND_FUNCTION(tvg_lottie_animation_expressions_supported)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_BOOL(tvg_lottie_animation_expressions_supported());
}

/* ThorVG's audio resolver: only the Lottie loader calls it. */
static void tvg_audio_resolver_trampoline(const Tvg_Audio_Info *info, void *data)
{
	zval args[2], retval;
	zend_object *o;

	object_init_ex(&args[0], tvg_audio_info_ce);
	o = Z_OBJ(args[0]);
	if (info != NULL) {
		if (info->src != NULL) {
			ZVAL_STRING(OBJ_PROP_NUM(o, 0), info->src);
		}
		if (info->mimeType != NULL) {
			ZVAL_STRING(OBJ_PROP_NUM(o, 1), info->mimeType);
		}
		ZVAL_LONG(OBJ_PROP_NUM(o, 2), (zend_long) info->size);
		ZVAL_DOUBLE(OBJ_PROP_NUM(o, 3), info->offset);
		ZVAL_DOUBLE(OBJ_PROP_NUM(o, 4), info->volume);
		ZVAL_BOOL(OBJ_PROP_NUM(o, 5), info->active);
		ZVAL_BOOL(OBJ_PROP_NUM(o, 6), info->embedded);
	}
	ZVAL_COPY(&args[1], &((tvg_callback *) data)->data);
	if (tvg_callback_call((tvg_callback *) data, args, 2, &retval)) {
		zval_ptr_dtor(&retval);
	}
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
}

ZEND_FUNCTION(tvg_lottie_animation_set_audio_resolver)
{
	zval *animation_zv, *resolver, *data;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_ZVAL(resolver)
		Z_PARAM_ZVAL(data)
	ZEND_PARSE_PARAMETERS_END();

	if (Z_TYPE_P(resolver) != IS_NULL && !zend_is_callable(resolver, 0, NULL)) {
		zend_argument_type_error(2, "must be a valid callback or null");
		RETURN_THROWS();
	}
	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	if (Z_TYPE_P(resolver) == IS_NULL) {
		RETURN_LONG((zend_long) tvg_lottie_animation_set_audio_resolver(animation, NULL, NULL));
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_set_audio_resolver(animation, tvg_audio_resolver_trampoline, tvg_callback_new(resolver, data)));
}

ZEND_FUNCTION(tvg_lottie_animation_set_volume)
{
	zval *animation_zv;
	double volume;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
		Z_PARAM_DOUBLE(volume)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_lottie_animation_set_volume(animation, (float) volume));
}

ZEND_FUNCTION(tvg_lottie_animation_get_volume)
{
	zval *animation_zv;
	Tvg_Animation animation;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(animation_zv, ANIMATION_CE)
	ZEND_PARSE_PARAMETERS_END();

	animation = tvg_animation_arg(animation_zv, 1);
	if (animation == NULL) {
		RETURN_THROWS();
	}
	RETURN_DOUBLE((double) tvg_lottie_animation_get_volume(animation));
}

/* ---- video ---- */

ZEND_FUNCTION(tvg_video_new)
{
	ZEND_PARSE_PARAMETERS_NONE();
	tvg_handle_new(TVG_K_VIDEO, tvg_video_new(), return_value);
}

ZEND_FUNCTION(tvg_video_del)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	tvg_handle_release(Z_OBJ_P(video_zv));
	RETURN_LONG((zend_long) tvg_video_del(video));
}

ZEND_FUNCTION(tvg_video_get_picture)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	tvg_paint_wrap(tvg_video_get_picture(video), return_value);
}

ZEND_FUNCTION(tvg_video_play)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_play(video));
}

ZEND_FUNCTION(tvg_video_pause)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_pause(video));
}

ZEND_FUNCTION(tvg_video_stop)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_stop(video));
}

ZEND_FUNCTION(tvg_video_seek)
{
	zval *video_zv;
	double seconds;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
		Z_PARAM_DOUBLE(seconds)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_seek(video, (float) seconds));
}

ZEND_FUNCTION(tvg_video_set_loop)
{
	zval *video_zv;
	bool on;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
		Z_PARAM_BOOL(on)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_set_loop(video, on));
}

ZEND_FUNCTION(tvg_video_get_loop)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_BOOL(tvg_video_get_loop(video));
}

ZEND_FUNCTION(tvg_video_set_volume)
{
	zval *video_zv;
	double volume;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
		Z_PARAM_DOUBLE(volume)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_set_volume(video, (float) volume));
}

ZEND_FUNCTION(tvg_video_get_volume)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_DOUBLE((double) tvg_video_get_volume(video));
}

ZEND_FUNCTION(tvg_video_set_mute)
{
	zval *video_zv;
	bool on;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
		Z_PARAM_BOOL(on)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) tvg_video_set_mute(video, on));
}

ZEND_FUNCTION(tvg_video_get_muted)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_BOOL(tvg_video_get_muted(video));
}

ZEND_FUNCTION(tvg_video_get_time)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_DOUBLE((double) tvg_video_get_time(video));
}

ZEND_FUNCTION(tvg_video_get_duration)
{
	zval *video_zv;
	Tvg_Video video;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(video_zv, VIDEO_CE)
	ZEND_PARSE_PARAMETERS_END();

	video = tvg_video_arg(video_zv, 1);
	if (video == NULL) {
		RETURN_THROWS();
	}
	RETURN_DOUBLE((double) tvg_video_get_duration(video));
}

void tvg_misc_minit(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
