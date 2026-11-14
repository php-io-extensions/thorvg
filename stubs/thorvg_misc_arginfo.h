/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 454271416f20bf5a8794f6ddc6cf5278bd4bacaf */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_saver_new, 0, 0, Tvg_Saver, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_saver_save_paint, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, saver, Tvg_Saver, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_saver_save_animation, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, saver, Tvg_Saver, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fps, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_saver_sync, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, saver, Tvg_Saver, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_saver_del arginfo_tvg_saver_sync

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_animation_new, 0, 0, Tvg_Animation, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_set_frame, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, no, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_animation_get_picture, 0, 1, Tvg_Paint, 1)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_get_frame, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(1, no, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_get_total_frame, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(1, cnt, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_get_duration, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(1, duration, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_set_segment, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, begin, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, end, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_get_segment, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(1, begin, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, end, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_animation_del, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_accessor_new, 0, 0, Tvg_Accessor, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_accessor_del, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, accessor, Tvg_Accessor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_accessor_set, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, accessor, Tvg_Accessor, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, func, IS_CALLABLE, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_accessor_generate_id, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_accessor_get_name, 0, 2, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, accessor, Tvg_Accessor, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_lottie_animation_new arginfo_tvg_animation_new

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_gen_slot, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, slot, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_apply_slot, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_lottie_animation_del_slot arginfo_tvg_lottie_animation_apply_slot

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_set_marker, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, marker, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_get_markers_cnt, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(1, cnt, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_get_marker, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, idx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_get_marker_info, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, idx, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, name, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(1, begin, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, end, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_tween, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, from, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, to, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, progress, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_tween_to, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, to, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_tween_go, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, progress, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_set_quality, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_expressions_supported, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_set_audio_resolver, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, resolver, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, data, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_set_volume, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
	ZEND_ARG_TYPE_INFO(0, volume, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_lottie_animation_get_volume, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, animation, Tvg_Animation, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_video_new, 0, 0, Tvg_Video, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_del, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_video_get_picture, 0, 1, Tvg_Paint, 1)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_video_play arginfo_tvg_video_del

#define arginfo_tvg_video_pause arginfo_tvg_video_del

#define arginfo_tvg_video_stop arginfo_tvg_video_del

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_seek, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_set_loop, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
	ZEND_ARG_TYPE_INFO(0, on, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_get_loop, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_set_volume, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
	ZEND_ARG_TYPE_INFO(0, volume, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_video_get_volume, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, video, Tvg_Video, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_video_set_mute arginfo_tvg_video_set_loop

#define arginfo_tvg_video_get_muted arginfo_tvg_video_get_loop

#define arginfo_tvg_video_get_time arginfo_tvg_video_get_volume

#define arginfo_tvg_video_get_duration arginfo_tvg_video_get_volume

ZEND_FUNCTION(tvg_saver_new);
ZEND_FUNCTION(tvg_saver_save_paint);
ZEND_FUNCTION(tvg_saver_save_animation);
ZEND_FUNCTION(tvg_saver_sync);
ZEND_FUNCTION(tvg_saver_del);
ZEND_FUNCTION(tvg_animation_new);
ZEND_FUNCTION(tvg_animation_set_frame);
ZEND_FUNCTION(tvg_animation_get_picture);
ZEND_FUNCTION(tvg_animation_get_frame);
ZEND_FUNCTION(tvg_animation_get_total_frame);
ZEND_FUNCTION(tvg_animation_get_duration);
ZEND_FUNCTION(tvg_animation_set_segment);
ZEND_FUNCTION(tvg_animation_get_segment);
ZEND_FUNCTION(tvg_animation_del);
ZEND_FUNCTION(tvg_accessor_new);
ZEND_FUNCTION(tvg_accessor_del);
ZEND_FUNCTION(tvg_accessor_set);
ZEND_FUNCTION(tvg_accessor_generate_id);
ZEND_FUNCTION(tvg_accessor_get_name);
ZEND_FUNCTION(tvg_lottie_animation_new);
ZEND_FUNCTION(tvg_lottie_animation_gen_slot);
ZEND_FUNCTION(tvg_lottie_animation_apply_slot);
ZEND_FUNCTION(tvg_lottie_animation_del_slot);
ZEND_FUNCTION(tvg_lottie_animation_set_marker);
ZEND_FUNCTION(tvg_lottie_animation_get_markers_cnt);
ZEND_FUNCTION(tvg_lottie_animation_get_marker);
ZEND_FUNCTION(tvg_lottie_animation_get_marker_info);
ZEND_FUNCTION(tvg_lottie_animation_tween);
ZEND_FUNCTION(tvg_lottie_animation_tween_to);
ZEND_FUNCTION(tvg_lottie_animation_tween_go);
ZEND_FUNCTION(tvg_lottie_animation_set_quality);
ZEND_FUNCTION(tvg_lottie_animation_expressions_supported);
ZEND_FUNCTION(tvg_lottie_animation_set_audio_resolver);
ZEND_FUNCTION(tvg_lottie_animation_set_volume);
ZEND_FUNCTION(tvg_lottie_animation_get_volume);
ZEND_FUNCTION(tvg_video_new);
ZEND_FUNCTION(tvg_video_del);
ZEND_FUNCTION(tvg_video_get_picture);
ZEND_FUNCTION(tvg_video_play);
ZEND_FUNCTION(tvg_video_pause);
ZEND_FUNCTION(tvg_video_stop);
ZEND_FUNCTION(tvg_video_seek);
ZEND_FUNCTION(tvg_video_set_loop);
ZEND_FUNCTION(tvg_video_get_loop);
ZEND_FUNCTION(tvg_video_set_volume);
ZEND_FUNCTION(tvg_video_get_volume);
ZEND_FUNCTION(tvg_video_set_mute);
ZEND_FUNCTION(tvg_video_get_muted);
ZEND_FUNCTION(tvg_video_get_time);
ZEND_FUNCTION(tvg_video_get_duration);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_saver_new, arginfo_tvg_saver_new)
	ZEND_FE(tvg_saver_save_paint, arginfo_tvg_saver_save_paint)
	ZEND_FE(tvg_saver_save_animation, arginfo_tvg_saver_save_animation)
	ZEND_FE(tvg_saver_sync, arginfo_tvg_saver_sync)
	ZEND_FE(tvg_saver_del, arginfo_tvg_saver_del)
	ZEND_FE(tvg_animation_new, arginfo_tvg_animation_new)
	ZEND_FE(tvg_animation_set_frame, arginfo_tvg_animation_set_frame)
	ZEND_FE(tvg_animation_get_picture, arginfo_tvg_animation_get_picture)
	ZEND_FE(tvg_animation_get_frame, arginfo_tvg_animation_get_frame)
	ZEND_FE(tvg_animation_get_total_frame, arginfo_tvg_animation_get_total_frame)
	ZEND_FE(tvg_animation_get_duration, arginfo_tvg_animation_get_duration)
	ZEND_FE(tvg_animation_set_segment, arginfo_tvg_animation_set_segment)
	ZEND_FE(tvg_animation_get_segment, arginfo_tvg_animation_get_segment)
	ZEND_FE(tvg_animation_del, arginfo_tvg_animation_del)
	ZEND_FE(tvg_accessor_new, arginfo_tvg_accessor_new)
	ZEND_FE(tvg_accessor_del, arginfo_tvg_accessor_del)
	ZEND_FE(tvg_accessor_set, arginfo_tvg_accessor_set)
	ZEND_FE(tvg_accessor_generate_id, arginfo_tvg_accessor_generate_id)
	ZEND_FE(tvg_accessor_get_name, arginfo_tvg_accessor_get_name)
	ZEND_FE(tvg_lottie_animation_new, arginfo_tvg_lottie_animation_new)
	ZEND_FE(tvg_lottie_animation_gen_slot, arginfo_tvg_lottie_animation_gen_slot)
	ZEND_FE(tvg_lottie_animation_apply_slot, arginfo_tvg_lottie_animation_apply_slot)
	ZEND_FE(tvg_lottie_animation_del_slot, arginfo_tvg_lottie_animation_del_slot)
	ZEND_FE(tvg_lottie_animation_set_marker, arginfo_tvg_lottie_animation_set_marker)
	ZEND_FE(tvg_lottie_animation_get_markers_cnt, arginfo_tvg_lottie_animation_get_markers_cnt)
	ZEND_FE(tvg_lottie_animation_get_marker, arginfo_tvg_lottie_animation_get_marker)
	ZEND_FE(tvg_lottie_animation_get_marker_info, arginfo_tvg_lottie_animation_get_marker_info)
	ZEND_FE(tvg_lottie_animation_tween, arginfo_tvg_lottie_animation_tween)
	ZEND_FE(tvg_lottie_animation_tween_to, arginfo_tvg_lottie_animation_tween_to)
	ZEND_FE(tvg_lottie_animation_tween_go, arginfo_tvg_lottie_animation_tween_go)
	ZEND_FE(tvg_lottie_animation_set_quality, arginfo_tvg_lottie_animation_set_quality)
	ZEND_FE(tvg_lottie_animation_expressions_supported, arginfo_tvg_lottie_animation_expressions_supported)
	ZEND_FE(tvg_lottie_animation_set_audio_resolver, arginfo_tvg_lottie_animation_set_audio_resolver)
	ZEND_FE(tvg_lottie_animation_set_volume, arginfo_tvg_lottie_animation_set_volume)
	ZEND_FE(tvg_lottie_animation_get_volume, arginfo_tvg_lottie_animation_get_volume)
	ZEND_FE(tvg_video_new, arginfo_tvg_video_new)
	ZEND_FE(tvg_video_del, arginfo_tvg_video_del)
	ZEND_FE(tvg_video_get_picture, arginfo_tvg_video_get_picture)
	ZEND_FE(tvg_video_play, arginfo_tvg_video_play)
	ZEND_FE(tvg_video_pause, arginfo_tvg_video_pause)
	ZEND_FE(tvg_video_stop, arginfo_tvg_video_stop)
	ZEND_FE(tvg_video_seek, arginfo_tvg_video_seek)
	ZEND_FE(tvg_video_set_loop, arginfo_tvg_video_set_loop)
	ZEND_FE(tvg_video_get_loop, arginfo_tvg_video_get_loop)
	ZEND_FE(tvg_video_set_volume, arginfo_tvg_video_set_volume)
	ZEND_FE(tvg_video_get_volume, arginfo_tvg_video_get_volume)
	ZEND_FE(tvg_video_set_mute, arginfo_tvg_video_set_mute)
	ZEND_FE(tvg_video_get_muted, arginfo_tvg_video_get_muted)
	ZEND_FE(tvg_video_get_time, arginfo_tvg_video_get_time)
	ZEND_FE(tvg_video_get_duration, arginfo_tvg_video_get_duration)
	ZEND_FE_END
};
