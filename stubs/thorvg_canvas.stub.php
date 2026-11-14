<?php

/** @generate-class-entries */

function tvg_engine_init(int $threads): int {}

function tvg_engine_term(): int {}

function tvg_swcanvas_create(int $op): ?Tvg_Canvas {}

/** $buffer: a string of at least $stride × $h × 4 bytes, kept alive by the canvas (ThorVG draws into it), or an address, trusted. */
function tvg_swcanvas_set_target(Tvg_Canvas $canvas, string|int $buffer, int $stride, int $w, int $h, int $cs): int {}

/**
 * Binding addition: the alpha byte of every pixel of a software canvas's buffer, described as
 * tvg_swcanvas_set_target() takes it: $h rows of $w bytes, top row first. $cs is one of the four
 * 32-bit colorspaces (alpha is the high byte of each pixel word in all of them). Call it after
 * tvg_canvas_sync(). A shape drawn in opaque white on a cleared buffer leaves its coverage there.
 */
function tvg_swcanvas_get_alpha(string|int $buffer, int $stride, int $w, int $h, int $cs): string {}

function tvg_glcanvas_create(int $op): ?Tvg_Canvas {}

function tvg_glcanvas_set_target(Tvg_Canvas $canvas, int $display, int $surface, int $context, int $id, int $w, int $h, int $cs): int {}

function tvg_wgcanvas_create(int $op): ?Tvg_Canvas {}

function tvg_wgcanvas_set_target(Tvg_Canvas $canvas, int $device, int $instance, int $target, int $w, int $h, int $cs, int $type): int {}

function tvg_wgcanvas_set_target_with_context(Tvg_Canvas $canvas, Tvg_WgContext $context, int $target, int $w, int $h, int $cs, int $type): int {}

function tvg_canvas_destroy(Tvg_Canvas $canvas): int {}

function tvg_canvas_add(Tvg_Canvas $canvas, Tvg_Paint $paint): int {}

function tvg_canvas_insert(Tvg_Canvas $canvas, Tvg_Paint $target, ?Tvg_Paint $at): int {}

function tvg_canvas_remove(Tvg_Canvas $canvas, Tvg_Paint $paint): int {}

function tvg_canvas_update(Tvg_Canvas $canvas): int {}

function tvg_canvas_draw(Tvg_Canvas $canvas, bool $clear): int {}

function tvg_canvas_sync(Tvg_Canvas $canvas): int {}

function tvg_canvas_get_dirty_regions_cnt(Tvg_Canvas $canvas): int {}

/** $regions: by reference, a list of $cnt Tvg_Region. */
function tvg_canvas_get_dirty_regions(Tvg_Canvas $canvas, ?array &$regions, int $cnt): int {}

function tvg_canvas_set_viewport(Tvg_Canvas $canvas, int $x, int $y, int $w, int $h): int {}
