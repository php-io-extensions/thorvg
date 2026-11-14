<?php

/** @generate-class-entries */

function tvg_linear_gradient_new(): ?Tvg_Gradient {}

function tvg_radial_gradient_new(): ?Tvg_Gradient {}

function tvg_conic_gradient_new(): ?Tvg_Gradient {}

function tvg_linear_gradient_set(Tvg_Gradient $grad, float $x1, float $y1, float $x2, float $y2): int {}

function tvg_linear_gradient_get(Tvg_Gradient $grad, ?float &$x1, ?float &$y1, ?float &$x2, ?float &$y2): int {}

function tvg_radial_gradient_set(Tvg_Gradient $grad, float $cx, float $cy, float $r, float $fx, float $fy, float $fr): int {}

function tvg_radial_gradient_get(Tvg_Gradient $grad, ?float &$cx, ?float &$cy, ?float &$r, ?float &$fx, ?float &$fy, ?float &$fr): int {}

function tvg_conic_gradient_set(Tvg_Gradient $grad, float $cx, float $cy, float $angle): int {}

function tvg_conic_gradient_get(Tvg_Gradient $grad, ?float &$cx, ?float &$cy, ?float &$angle): int {}

/** $color_stop: a list of Tvg_Color_Stop; $cnt above its length is refused. */
function tvg_gradient_set_color_stops(Tvg_Gradient $grad, array $color_stop, int $cnt): int {}

function tvg_gradient_get_color_stops(Tvg_Gradient $grad, ?array &$color_stop, ?int &$cnt): int {}

function tvg_gradient_set_spread(Tvg_Gradient $grad, int $spread): int {}

function tvg_gradient_get_spread(Tvg_Gradient $grad, ?int &$spread): int {}

function tvg_gradient_set_transform(Tvg_Gradient $grad, Tvg_Matrix $m): int {}

function tvg_gradient_get_transform(Tvg_Gradient $grad, Tvg_Matrix $m): int {}

function tvg_gradient_get_type(Tvg_Gradient $grad, ?int &$type): int {}

function tvg_gradient_duplicate(Tvg_Gradient $grad): ?Tvg_Gradient {}

function tvg_gradient_del(Tvg_Gradient $grad): int {}
