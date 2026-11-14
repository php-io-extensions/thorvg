<?php

/** @generate-class-entries */

/** The Tvg_Paint object holds a reference while it lives, so this frees nothing PHP can still reach. */
function tvg_paint_rel(Tvg_Paint $paint): int {}

function tvg_paint_ref(Tvg_Paint $paint): int {}

function tvg_paint_unref(Tvg_Paint $paint, bool $free): int {}

function tvg_paint_get_ref(Tvg_Paint $paint): int {}

function tvg_paint_set_visible(Tvg_Paint $paint, bool $visible): int {}

function tvg_paint_get_visible(Tvg_Paint $paint): bool {}

function tvg_paint_get_id(Tvg_Paint $paint): int {}

function tvg_paint_set_id(Tvg_Paint $paint, int $id): int {}

/** The address set with tvg_paint_set_data(), 0 for none. */
function tvg_paint_get_data(Tvg_Paint $paint): int {}

/** $data: an address, trusted; 0 is NULL. */
function tvg_paint_set_data(Tvg_Paint $paint, int $data): int {}

function tvg_paint_scale(Tvg_Paint $paint, float $factor): int {}

function tvg_paint_rotate(Tvg_Paint $paint, float $degree): int {}

function tvg_paint_translate(Tvg_Paint $paint, float $x, float $y): int {}

function tvg_paint_set_transform(Tvg_Paint $paint, Tvg_Matrix $m): int {}

function tvg_paint_get_transform(Tvg_Paint $paint, Tvg_Matrix $m): int {}

function tvg_paint_set_opacity(Tvg_Paint $paint, int $opacity): int {}

function tvg_paint_get_opacity(Tvg_Paint $paint, ?int &$opacity): int {}

function tvg_paint_duplicate(Tvg_Paint $paint): ?Tvg_Paint {}

function tvg_paint_intersects(Tvg_Paint $paint, int $x, int $y, int $w, int $h): bool {}

function tvg_paint_intersects_region(Tvg_Paint $paint, int $x, int $y, int $w, int $h, bool $visibleOnly): bool {}

function tvg_paint_get_aabb(Tvg_Paint $paint, ?float &$x, ?float &$y, ?float &$w, ?float &$h): int {}

/** $pt4: by reference, a list of 4 Tvg_Point. */
function tvg_paint_get_obb(Tvg_Paint $paint, ?array &$pt4): int {}

function tvg_paint_set_mask_method(Tvg_Paint $paint, ?Tvg_Paint $target, int $method): int {}

/**
 * $target: by reference, the mask target. The header types it `const Tvg_Paint` but documents it as
 * [out], and ThorVG 1.1.3 writes the target's address through it: it is bound as the out-parameter it is.
 */
function tvg_paint_get_mask_method(Tvg_Paint $paint, ?Tvg_Paint &$target, ?int &$method): int {}

function tvg_paint_set_clip(Tvg_Paint $paint, ?Tvg_Paint $clipper): int {}

function tvg_paint_get_clip(Tvg_Paint $paint): ?Tvg_Paint {}

function tvg_paint_get_parent(Tvg_Paint $paint): ?Tvg_Paint {}

function tvg_paint_get_type(Tvg_Paint $paint, ?int &$type): int {}

function tvg_paint_set_blend_method(Tvg_Paint $paint, int $method): int {}
