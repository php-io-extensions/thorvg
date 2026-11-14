<?php

/** @generate-class-entries */

/**
 * Tvg_Canvas. Destroyed with the object, or by tvg_canvas_destroy(); keeps its target string alive.
 *
 * @not-serializable
 */
final class Tvg_Canvas
{
    private function __construct() {}
}

/**
 * Tvg_Paint: a shape, scene, picture or text. Holds one ThorVG reference while the object lives.
 *
 * @not-serializable
 */
final class Tvg_Paint
{
    private function __construct() {}
}

/**
 * Tvg_Gradient. Deleted with the object while PHP owns it; owned by the paint it is set on after that.
 *
 * @not-serializable
 */
final class Tvg_Gradient
{
    private function __construct() {}
}

/**
 * Tvg_Saver. Syncs and is deleted with the object, or by tvg_saver_del().
 *
 * @not-serializable
 */
final class Tvg_Saver
{
    private function __construct() {}
}

/**
 * Tvg_Animation. Deleted with the object, or by tvg_animation_del().
 *
 * @not-serializable
 */
final class Tvg_Animation
{
    private function __construct() {}
}

/**
 * Tvg_Accessor. Deleted with the object, or by tvg_accessor_del().
 *
 * @not-serializable
 */
final class Tvg_Accessor
{
    private function __construct() {}
}

/**
 * Tvg_Video. Deleted with the object, or by tvg_video_del().
 *
 * @not-serializable
 */
final class Tvg_Video
{
    private function __construct() {}
}

/** Tvg_Point. Floats are stored as C float when they cross into ThorVG. */
final class Tvg_Point
{
    public float $x = 0.0;
    public float $y = 0.0;

    public function __construct(float $x = 0.0, float $y = 0.0) {}
}

/** Tvg_Matrix. A new matrix is the zero matrix, as in C. */
final class Tvg_Matrix
{
    public float $e11 = 0.0;
    public float $e12 = 0.0;
    public float $e13 = 0.0;
    public float $e21 = 0.0;
    public float $e22 = 0.0;
    public float $e23 = 0.0;
    public float $e31 = 0.0;
    public float $e32 = 0.0;
    public float $e33 = 0.0;

    public function __construct(
        float $e11 = 0.0, float $e12 = 0.0, float $e13 = 0.0,
        float $e21 = 0.0, float $e22 = 0.0, float $e23 = 0.0,
        float $e31 = 0.0, float $e32 = 0.0, float $e33 = 0.0,
    ) {}
}

/** Tvg_Region. */
final class Tvg_Region
{
    public int $xMin = 0;
    public int $yMin = 0;
    public int $xMax = 0;
    public int $yMax = 0;

    public function __construct(int $xMin = 0, int $yMin = 0, int $xMax = 0, int $yMax = 0) {}
}

/** Tvg_Color_Stop. r, g, b, a are uint8_t: 0..255. */
final class Tvg_Color_Stop
{
    public float $offset = 0.0;
    public int $r = 0;
    public int $g = 0;
    public int $b = 0;
    public int $a = 0;

    public function __construct(float $offset = 0.0, int $r = 0, int $g = 0, int $b = 0, int $a = 0) {}
}

/** Tvg_Text_Metrics. */
final class Tvg_Text_Metrics
{
    public float $ascent = 0.0;
    public float $descent = 0.0;
    public float $linegap = 0.0;
    public float $advance = 0.0;

    public function __construct(float $ascent = 0.0, float $descent = 0.0, float $linegap = 0.0, float $advance = 0.0) {}
}

/** Tvg_Glyph_Metrics. min and max are built by the constructor. */
final class Tvg_Glyph_Metrics
{
    public float $advance = 0.0;
    public float $bearing = 0.0;
    public Tvg_Point $min;
    public Tvg_Point $max;

    public function __construct(float $advance = 0.0, float $bearing = 0.0, ?Tvg_Point $min = null, ?Tvg_Point $max = null) {}
}

/** Tvg_WgContext: WebGPU handles as addresses, trusted (0 is NULL). */
final class Tvg_WgContext
{
    public int $instance = 0;
    public int $adapter = 0;
    public int $device = 0;

    public function __construct(int $instance = 0, int $adapter = 0, int $device = 0) {}
}

/** Tvg_Audio_Info: what an audio resolver is given. */
final class Tvg_Audio_Info
{
    public ?string $src = null;
    public ?string $mimeType = null;
    public int $size = 0;
    public float $offset = 0.0;
    public float $volume = 0.0;
    public bool $active = false;
    public bool $embedded = false;

    public function __construct() {}
}
