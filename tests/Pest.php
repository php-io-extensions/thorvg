<?php

declare(strict_types=1);

if (! extension_loaded('thorvg')) {
    throw new RuntimeException('The thorvg extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/** A TrueType font on this machine, or null (font tests skip without one). */
function tvg_test_font_file(): ?string
{
    foreach ([
        '/System/Library/Fonts/Supplemental/Arial.ttf',
        '/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',
        '/usr/share/fonts/TTF/DejaVuSans.ttf',
    ] as $file) {
        if (is_file($file)) {
            return $file;
        }
    }

    return null;
}

tvg_engine_init(0);

/** A canvas drawing into $buffer (built at run time: ThorVG writes into it), straight RGBA bytes. */
function tvg_test_canvas(?string &$buffer, int $width = 8, int $height = 8): Tvg_Canvas
{
    $buffer = str_repeat("\0", $width * $height * 4);
    $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);
    expect(tvg_swcanvas_set_target($canvas, $buffer, $width, $width, $height, TVG_COLORSPACE_ABGR8888S))->toBe(TVG_RESULT_SUCCESS);

    return $canvas;
}

/** The RGBA hex of pixel (x, y) in a $width-wide straight RGBA buffer. */
function tvg_test_pixel(string $buffer, int $x, int $y, int $width = 8): string
{
    return bin2hex(substr($buffer, ($y * $width + $x) * 4, 4));
}

function tvg_test_draw(Tvg_Canvas $canvas): void
{
    expect(tvg_canvas_draw($canvas, true))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_canvas_sync($canvas))->toBe(TVG_RESULT_SUCCESS);
}

/** A rect shape filled with an opaque colour. */
function tvg_test_rect(float $x, float $y, float $w, float $h, array $rgba): Tvg_Paint
{
    $shape = tvg_shape_new();
    tvg_shape_append_rect($shape, $x, $y, $w, $h, 0, 0, true);
    tvg_shape_set_fill_color($shape, ...$rgba);

    return $shape;
}
