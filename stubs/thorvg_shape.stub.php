<?php

/** @generate-class-entries */

function tvg_shape_new(): ?Tvg_Paint {}

function tvg_shape_reset(Tvg_Paint $paint): int {}

function tvg_shape_move_to(Tvg_Paint $paint, float $x, float $y): int {}

function tvg_shape_line_to(Tvg_Paint $paint, float $x, float $y): int {}

function tvg_shape_cubic_to(Tvg_Paint $paint, float $cx1, float $cy1, float $cx2, float $cy2, float $x, float $y): int {}

function tvg_shape_close(Tvg_Paint $paint): int {}

function tvg_shape_append_rect(Tvg_Paint $paint, float $x, float $y, float $w, float $h, float $rx, float $ry, bool $cw): int {}

function tvg_shape_append_circle(Tvg_Paint $paint, float $cx, float $cy, float $rx, float $ry, bool $cw): int {}

/** $cmds: TVG_PATH_COMMAND_* ints; $pts: Tvg_Point. A count above its list's length is refused. */
function tvg_shape_append_path(Tvg_Paint $paint, array $cmds, int $cmdCnt, array $pts, int $ptsCnt): int {}

/** $cmds: by reference, TVG_PATH_COMMAND_* ints; $pts: by reference, Tvg_Point. */
function tvg_shape_get_path(Tvg_Paint $paint, ?array &$cmds, ?int &$cmdsCnt, ?array &$pts, ?int &$ptsCnt): int {}

/**
 * Binding addition: the outline of the shape's stroke, as tvg_shape_get_path() gives a path,
 * from ThorVG's own CPU stroker. In the shape's own coordinates; width, cap, join and miter limit
 * are the shape's, its dash and trim are not applied. Empty when the shape has no stroke width.
 * Reads ThorVG internals, so a ThorVG update may change it.
 *
 * $cmds: by reference, TVG_PATH_COMMAND_* ints; $pts: by reference, Tvg_Point.
 */
function tvg_shape_get_stroke_outline(Tvg_Paint $paint, ?array &$cmds, ?int &$cmdsCnt, ?array &$pts, ?int &$ptsCnt): int {}

function tvg_shape_set_stroke_width(Tvg_Paint $paint, float $width): int {}

function tvg_shape_get_stroke_width(Tvg_Paint $paint, ?float &$width): int {}

function tvg_shape_set_stroke_color(Tvg_Paint $paint, int $r, int $g, int $b, int $a): int {}

function tvg_shape_get_stroke_color(Tvg_Paint $paint, ?int &$r, ?int &$g, ?int &$b, ?int &$a): int {}

function tvg_shape_set_stroke_gradient(Tvg_Paint $paint, Tvg_Gradient $grad): int {}

function tvg_shape_get_stroke_gradient(Tvg_Paint $paint, ?Tvg_Gradient &$grad): int {}

function tvg_shape_set_stroke_dash(Tvg_Paint $paint, ?array $dashPattern, int $cnt, float $offset): int {}

function tvg_shape_get_stroke_dash(Tvg_Paint $paint, ?array &$dashPattern, ?int &$cnt, ?float &$offset): int {}

function tvg_shape_set_stroke_cap(Tvg_Paint $paint, int $cap): int {}

function tvg_shape_get_stroke_cap(Tvg_Paint $paint, ?int &$cap): int {}

function tvg_shape_set_stroke_join(Tvg_Paint $paint, int $join): int {}

function tvg_shape_get_stroke_join(Tvg_Paint $paint, ?int &$join): int {}

function tvg_shape_set_stroke_miterlimit(Tvg_Paint $paint, float $miterlimit): int {}

function tvg_shape_get_stroke_miterlimit(Tvg_Paint $paint, ?float &$miterlimit): int {}

function tvg_shape_set_trimpath(Tvg_Paint $paint, float $begin, float $end, bool $simultaneous): int {}

function tvg_shape_set_fill_color(Tvg_Paint $paint, int $r, int $g, int $b, int $a): int {}

function tvg_shape_get_fill_color(Tvg_Paint $paint, ?int &$r, ?int &$g, ?int &$b, ?int &$a): int {}

function tvg_shape_set_fill_rule(Tvg_Paint $paint, int $rule): int {}

function tvg_shape_get_fill_rule(Tvg_Paint $paint, ?int &$rule): int {}

function tvg_shape_set_paint_order(Tvg_Paint $paint, bool $strokeFirst): int {}

function tvg_shape_set_gradient(Tvg_Paint $paint, Tvg_Gradient $grad): int {}

function tvg_shape_get_gradient(Tvg_Paint $paint, ?Tvg_Gradient &$grad): int {}
