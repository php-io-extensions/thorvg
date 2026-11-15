<?php

/** @generate-class-entries */

function tvg_picture_new(): ?Tvg_Paint {}

function tvg_picture_load(Tvg_Paint $picture, string $path): int {}

/** $data: a string of at least $w × $h × 4 bytes or an address, trusted. Without $copy, a string is kept alive until the request ends. */
function tvg_picture_load_raw(Tvg_Paint $picture, string|int $data, int $w, int $h, int $cs, bool $copy): int {}

/** Binding addition, the counterpart of tvg_swcanvas_get_alpha: each byte c of $alpha (w * h) loaded as the ARGB8888 pixel 0xCC000000 (ThorVG copies it), for an alpha mask. */
function tvg_picture_load_alpha(Tvg_Paint $picture, string $alpha, int $w, int $h): int {}

/** $data: a string of at least $size bytes or an address, trusted. Without $copy, a string is kept alive until the request ends. */
function tvg_picture_load_data(Tvg_Paint $picture, string|int $data, int $size, ?string $mimetype, ?string $rpath, bool $copy): int {}

/** $resolver(Tvg_Paint $paint, string $src, mixed $data): bool. Only ThorVG's Lottie loader calls it, which this build does not have. */
function tvg_picture_set_asset_resolver(Tvg_Paint $picture, ?callable $resolver, mixed $data): int {}

function tvg_picture_set_size(Tvg_Paint $picture, float $w, float $h): int {}

function tvg_picture_get_size(Tvg_Paint $picture, ?float &$w, ?float &$h): int {}

function tvg_picture_set_origin(Tvg_Paint $picture, float $x, float $y): int {}

function tvg_picture_get_origin(Tvg_Paint $picture, ?float &$x, ?float &$y): int {}

function tvg_picture_get_paint(Tvg_Paint $picture, int $id): ?Tvg_Paint {}

function tvg_picture_set_filter(Tvg_Paint $picture, int $method): int {}

function tvg_picture_set_accessible(Tvg_Paint $picture, bool $accessible): int {}

function tvg_scene_new(): ?Tvg_Paint {}

function tvg_scene_add(Tvg_Paint $scene, Tvg_Paint $paint): int {}

function tvg_scene_insert(Tvg_Paint $scene, Tvg_Paint $target, ?Tvg_Paint $at): int {}

function tvg_scene_remove(Tvg_Paint $scene, Tvg_Paint $paint): int {}

function tvg_scene_clear_effects(Tvg_Paint $scene): int {}

function tvg_scene_add_effect_gaussian_blur(Tvg_Paint $scene, float $sigma, int $direction, int $border, int $quality): int {}

function tvg_scene_add_effect_motion_blur(Tvg_Paint $scene, float $distance, float $angle, int $quality): int {}

function tvg_scene_add_effect_drop_shadow(Tvg_Paint $scene, int $r, int $g, int $b, int $a, float $angle, float $distance, float $sigma, int $quality): int {}

function tvg_scene_add_effect_fill(Tvg_Paint $scene, int $r, int $g, int $b, int $a): int {}

function tvg_scene_add_effect_tint(Tvg_Paint $scene, int $black_r, int $black_g, int $black_b, int $white_r, int $white_g, int $white_b, float $intensity): int {}

function tvg_scene_add_effect_tritone(Tvg_Paint $scene, int $shadow_r, int $shadow_g, int $shadow_b, int $midtone_r, int $midtone_g, int $midtone_b, int $highlight_r, int $highlight_g, int $highlight_b, int $blend): int {}

function tvg_text_new(): ?Tvg_Paint {}

function tvg_text_set_font(Tvg_Paint $text, ?string $name): int {}

function tvg_text_set_size(Tvg_Paint $text, float $size): int {}

function tvg_text_set_text(Tvg_Paint $text, ?string $utf8): int {}

function tvg_text_align(Tvg_Paint $text, float $x, float $y): int {}

function tvg_text_layout(Tvg_Paint $text, float $w, float $h): int {}

function tvg_text_wrap_mode(Tvg_Paint $text, int $mode): int {}

function tvg_text_line_count(Tvg_Paint $text): int {}

function tvg_text_spacing(Tvg_Paint $text, float $letter, float $line): int {}

function tvg_text_set_italic(Tvg_Paint $text, float $shear): int {}

function tvg_text_set_outline(Tvg_Paint $text, float $width, int $r, int $g, int $b): int {}

function tvg_text_set_color(Tvg_Paint $text, int $r, int $g, int $b): int {}

function tvg_text_set_gradient(Tvg_Paint $text, Tvg_Gradient $gradient): int {}

function tvg_text_get_text_metrics(Tvg_Paint $text, Tvg_Text_Metrics $metrics): int {}

/** $next: by reference, the byte offset in $ch of the character after the one measured. */
function tvg_text_get_glyph_metrics(Tvg_Paint $text, string $ch, Tvg_Glyph_Metrics $metrics, ?int &$next): int {}

function tvg_font_load(string $path): int {}

/** $data: a string of at least $size bytes or an address, trusted. Without $copy, a string is kept alive and the font unloaded when the request ends. */
function tvg_font_load_data(string $name, string|int $data, int $size, ?string $mimetype, bool $copy): int {}

function tvg_font_unload(string $path): int {}
