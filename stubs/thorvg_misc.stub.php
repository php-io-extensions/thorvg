<?php

/** @generate-class-entries */

function tvg_saver_new(): ?Tvg_Saver {}

function tvg_saver_save_paint(Tvg_Saver $saver, Tvg_Paint $paint, string $path, int $quality): int {}

function tvg_saver_save_animation(Tvg_Saver $saver, Tvg_Animation $animation, string $path, int $quality, int $fps): int {}

function tvg_saver_sync(Tvg_Saver $saver): int {}

function tvg_saver_del(Tvg_Saver $saver): int {}

function tvg_animation_new(): ?Tvg_Animation {}

function tvg_animation_set_frame(Tvg_Animation $animation, float $no): int {}

function tvg_animation_get_picture(Tvg_Animation $animation): ?Tvg_Paint {}

function tvg_animation_get_frame(Tvg_Animation $animation, ?float &$no): int {}

function tvg_animation_get_total_frame(Tvg_Animation $animation, ?float &$cnt): int {}

function tvg_animation_get_duration(Tvg_Animation $animation, ?float &$duration): int {}

function tvg_animation_set_segment(Tvg_Animation $animation, float $begin, float $end): int {}

function tvg_animation_get_segment(Tvg_Animation $animation, ?float &$begin, ?float &$end): int {}

function tvg_animation_del(Tvg_Animation $animation): int {}

function tvg_accessor_new(): ?Tvg_Accessor {}

function tvg_accessor_del(Tvg_Accessor $accessor): int {}

/** $func(Tvg_Paint $paint, mixed $data): bool, called synchronously for each paint; false stops the walk. */
function tvg_accessor_set(Tvg_Accessor $accessor, Tvg_Paint $paint, callable $func, mixed $data): int {}

function tvg_accessor_generate_id(string $name): int {}

function tvg_accessor_get_name(Tvg_Accessor $accessor, int $id): ?string {}

function tvg_lottie_animation_new(): ?Tvg_Animation {}

function tvg_lottie_animation_gen_slot(Tvg_Animation $animation, string $slot): int {}

function tvg_lottie_animation_apply_slot(Tvg_Animation $animation, int $id): int {}

function tvg_lottie_animation_del_slot(Tvg_Animation $animation, int $id): int {}

function tvg_lottie_animation_set_marker(Tvg_Animation $animation, string $marker): int {}

function tvg_lottie_animation_get_markers_cnt(Tvg_Animation $animation, ?int &$cnt): int {}

function tvg_lottie_animation_get_marker(Tvg_Animation $animation, int $idx, ?string &$name): int {}

function tvg_lottie_animation_get_marker_info(Tvg_Animation $animation, int $idx, ?string &$name, ?float &$begin, ?float &$end): int {}

function tvg_lottie_animation_tween(Tvg_Animation $animation, float $from, float $to, float $progress): int {}

function tvg_lottie_animation_tween_to(Tvg_Animation $animation, float $to): int {}

function tvg_lottie_animation_tween_go(Tvg_Animation $animation, float $progress): int {}

function tvg_lottie_animation_set_quality(Tvg_Animation $animation, int $value): int {}

function tvg_lottie_animation_expressions_supported(): bool {}

/** $resolver(Tvg_Audio_Info $info, mixed $data): void. This build has no Lottie loader. */
function tvg_lottie_animation_set_audio_resolver(Tvg_Animation $animation, ?callable $resolver, mixed $data): int {}

function tvg_lottie_animation_set_volume(Tvg_Animation $animation, float $volume): int {}

function tvg_lottie_animation_get_volume(Tvg_Animation $animation): float {}

function tvg_video_new(): ?Tvg_Video {}

function tvg_video_del(Tvg_Video $video): int {}

function tvg_video_get_picture(Tvg_Video $video): ?Tvg_Paint {}

function tvg_video_play(Tvg_Video $video): int {}

function tvg_video_pause(Tvg_Video $video): int {}

function tvg_video_stop(Tvg_Video $video): int {}

function tvg_video_seek(Tvg_Video $video, float $seconds): int {}

function tvg_video_set_loop(Tvg_Video $video, bool $on): int {}

function tvg_video_get_loop(Tvg_Video $video): bool {}

function tvg_video_set_volume(Tvg_Video $video, float $volume): int {}

function tvg_video_get_volume(Tvg_Video $video): float {}

function tvg_video_set_mute(Tvg_Video $video, bool $on): int {}

function tvg_video_get_muted(Tvg_Video $video): bool {}

function tvg_video_get_time(Tvg_Video $video): float {}

function tvg_video_get_duration(Tvg_Video $video): float {}
