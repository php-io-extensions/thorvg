<?php

declare(strict_types=1);

it('draws an axis-aligned rect with exact pixels and straight alpha', function (): void {
    $canvas = tvg_test_canvas($buffer);
    tvg_canvas_add($canvas, tvg_test_rect(2, 2, 4, 4, [255, 0, 0, 255]));
    tvg_canvas_add($canvas, tvg_test_rect(0, 0, 8, 1, [0, 0, 255, 128]));
    tvg_test_draw($canvas);

    expect(tvg_test_pixel($buffer, 3, 3))->toBe('ff0000ff')
        ->and(tvg_test_pixel($buffer, 2, 2))->toBe('ff0000ff')
        ->and(tvg_test_pixel($buffer, 6, 6))->toBe('00000000')
        ->and(tvg_test_pixel($buffer, 0, 0))->toBe('0000ff80');
});

it('draws BGRA with the ARGB8888S colorspace', function (): void {
    $buffer = str_repeat("\0", 16);
    $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);
    tvg_swcanvas_set_target($canvas, $buffer, 2, 2, 2, TVG_COLORSPACE_ARGB8888S);
    tvg_canvas_add($canvas, tvg_test_rect(0, 0, 2, 2, [255, 0, 0, 255]));
    tvg_test_draw($canvas);

    expect(bin2hex(substr($buffer, 0, 4)))->toBe('0000ffff');
});

it('inserts, removes and keeps order', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $red = tvg_test_rect(0, 0, 8, 8, [255, 0, 0, 255]);
    $green = tvg_test_rect(0, 0, 8, 8, [0, 255, 0, 255]);
    tvg_canvas_add($canvas, $red);
    expect(tvg_canvas_insert($canvas, $green, $red))->toBe(TVG_RESULT_SUCCESS);
    tvg_test_draw($canvas);
    expect(tvg_test_pixel($buffer, 0, 0))->toBe('ff0000ff');

    expect(tvg_canvas_remove($canvas, $red))->toBe(TVG_RESULT_SUCCESS);
    tvg_test_draw($canvas);
    expect(tvg_test_pixel($buffer, 0, 0))->toBe('00ff00ff');
});

it('keeps paints added to a canvas alive after PHP drops them', function (): void {
    $canvas = tvg_test_canvas($buffer);
    tvg_canvas_add($canvas, tvg_test_rect(0, 0, 8, 8, [1, 2, 3, 255]));
    gc_collect_cycles();
    tvg_test_draw($canvas);

    expect(tvg_test_pixel($buffer, 4, 4))->toBe('010203ff');
});

it('keeps its target string alive and reports a released canvas', function (): void {
    $canvas = (function (): Tvg_Canvas {
        $buffer = str_repeat("\0", 64);
        $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);
        tvg_swcanvas_set_target($canvas, $buffer, 4, 4, 4, TVG_COLORSPACE_ABGR8888S);

        return $canvas;
    })();
    tvg_canvas_add($canvas, tvg_test_rect(0, 0, 4, 4, [9, 9, 9, 255]));
    tvg_test_draw($canvas);

    expect(tvg_canvas_destroy($canvas))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_canvas_draw($canvas, true))->toThrow(ValueError::class, 'released Tvg_Canvas');
});

it('refuses short, interned and oversized targets', function (): void {
    $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);

    expect(fn () => tvg_swcanvas_set_target($canvas, str_repeat("\0", 8), 4, 4, 4, TVG_COLORSPACE_ABGR8888S))->toThrow(ValueError::class, 'must hold 64 bytes')
        ->and(fn () => tvg_swcanvas_set_target($canvas, 'abcd', 1, 1, 1, TVG_COLORSPACE_ABGR8888S))->toThrow(ValueError::class, 'interned')
        ->and(fn () => tvg_swcanvas_set_target($canvas, str_repeat("\0", 4), 1, 1, 1, 99))->toThrow(ValueError::class, 'TVG_COLORSPACE_')
        ->and(fn () => tvg_swcanvas_set_target($canvas, str_repeat("\0", 4), -1, 1, 1, 2))->toThrow(ValueError::class);
});

it('reports dirty regions within their count', function (): void {
    $buffer = str_repeat("\0", 64 * 64 * 4);
    $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_SMART_RENDER);
    tvg_swcanvas_set_target($canvas, $buffer, 64, 64, 64, TVG_COLORSPACE_ABGR8888S);
    $shape = tvg_test_rect(0, 0, 10, 10, [255, 255, 255, 255]);
    tvg_canvas_add($canvas, $shape);
    tvg_test_draw($canvas);
    tvg_paint_translate($shape, 20, 20);
    tvg_canvas_update($canvas);
    $count = tvg_canvas_get_dirty_regions_cnt($canvas);

    expect(tvg_canvas_get_dirty_regions($canvas, $regions, $count))->toBeInt()
        ->and($regions)->toHaveCount($count)
        ->and(fn () => tvg_canvas_get_dirty_regions($canvas, $regions, $count + 1))->toThrow(ValueError::class);
    tvg_canvas_sync($canvas);
});

it('has no GL or WebGPU engine in this build', function (): void {
    expect(tvg_glcanvas_create(TVG_ENGINE_OPTION_DEFAULT))->toBeNull()
        ->and(tvg_wgcanvas_create(TVG_ENGINE_OPTION_DEFAULT))->toBeNull();
});

it('reads a canvas buffer\'s alpha bytes in one call (binding addition)', function (): void {
    $buffer = str_repeat("\0", 4 * 2 * 4);   // stride 4 pixels, 3 wide, 2 high
    $canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_NONE);
    tvg_swcanvas_set_target($canvas, $buffer, 4, 3, 2, TVG_COLORSPACE_ARGB8888);
    tvg_canvas_add($canvas, tvg_test_rect(1, 0, 2, 1, [255, 255, 255, 255]));
    tvg_test_draw($canvas);

    expect(bin2hex(tvg_swcanvas_get_alpha($buffer, 4, 3, 2, TVG_COLORSPACE_ARGB8888)))->toBe('00ffff000000')
        ->and(fn () => tvg_swcanvas_get_alpha($buffer, 4, 5, 2, TVG_COLORSPACE_ARGB8888))->toThrow(ValueError::class)
        ->and(fn () => tvg_swcanvas_get_alpha($buffer, 4, 3, 3, TVG_COLORSPACE_ARGB8888))->toThrow(ValueError::class)
        ->and(fn () => tvg_swcanvas_get_alpha($buffer, 4, 3, 2, TVG_COLORSPACE_GRAYSCALE8))->toThrow(ValueError::class)
        ->and(fn () => tvg_swcanvas_get_alpha(0, 4, 3, 2, TVG_COLORSPACE_ARGB8888))->toThrow(ValueError::class);
});
