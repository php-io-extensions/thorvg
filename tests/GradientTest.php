<?php

declare(strict_types=1);

function tvg_test_stops(): array
{
    return [new Tvg_Color_Stop(0.0, 255, 0, 0, 255), new Tvg_Color_Stop(1.0, 0, 0, 255, 255)];
}

it('sets and reads linear, radial and conic geometry', function (): void {
    $linear = tvg_linear_gradient_new();
    $radial = tvg_radial_gradient_new();
    $conic = tvg_conic_gradient_new();
    tvg_linear_gradient_set($linear, 1, 2, 3, 4);
    tvg_radial_gradient_set($radial, 1, 2, 3, 4, 5, 6);
    tvg_conic_gradient_set($conic, 1, 2, 30);
    tvg_linear_gradient_get($linear, $x1, $y1, $x2, $y2);
    tvg_radial_gradient_get($radial, $cx, $cy, $r, $fx, $fy, $fr);
    tvg_conic_gradient_get($conic, $ccx, $ccy, $angle);
    tvg_gradient_get_type($conic, $type);

    expect([$x1, $y1, $x2, $y2])->toBe([1.0, 2.0, 3.0, 4.0])
        ->and([$cx, $cy, $r, $fx, $fy, $fr])->toBe([1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
        ->and([$ccx, $ccy, $angle])->toBe([1.0, 2.0, 30.0])
        ->and($type)->toBe(TVG_TYPE_CONIC_GRAD)
        ->and(fn () => tvg_linear_gradient_set($radial, 0, 0, 1, 1))->toThrow(TypeError::class, 'linear');
});

it('round-trips colour stops, spread and transform', function (): void {
    $gradient = tvg_linear_gradient_new();
    tvg_gradient_set_color_stops($gradient, tvg_test_stops(), 2);
    tvg_gradient_set_spread($gradient, TVG_STROKE_FILL_REFLECT);
    tvg_gradient_set_transform($gradient, new Tvg_Matrix(2, 0, 0, 0, 2, 0, 0, 0, 1));
    tvg_gradient_get_color_stops($gradient, $stops, $count);
    tvg_gradient_get_spread($gradient, $spread);
    tvg_gradient_get_transform($gradient, $m = new Tvg_Matrix());

    expect($count)->toBe(2)
        ->and([$stops[1]->offset, $stops[1]->b, $stops[1]->a])->toBe([1.0, 255, 255])
        ->and($spread)->toBe(TVG_STROKE_FILL_REFLECT)
        ->and($m->e11)->toBe(2.0)
        ->and(fn () => tvg_gradient_set_color_stops($gradient, [new Tvg_Color_Stop(0, 300)], 1))->toThrow(ValueError::class)
        ->and(fn () => tvg_gradient_set_color_stops($gradient, tvg_test_stops(), 3))->toThrow(ValueError::class);
});

it('paints a linear gradient left to right', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $gradient = tvg_linear_gradient_new();
    tvg_linear_gradient_set($gradient, 0, 0, 8, 0);
    tvg_gradient_set_color_stops($gradient, tvg_test_stops(), 2);
    $shape = tvg_shape_new();
    tvg_shape_append_rect($shape, 0, 0, 8, 8, 0, 0, true);
    tvg_shape_set_gradient($shape, $gradient);
    tvg_canvas_add($canvas, $shape);
    tvg_test_draw($canvas);

    $left = hexdec(substr(tvg_test_pixel($buffer, 0, 4), 0, 2));
    $right = hexdec(substr(tvg_test_pixel($buffer, 7, 4), 0, 2));
    expect($left)->toBeGreaterThan($right);
});

it('hands a gradient over to its shape and lends it back', function (): void {
    $shape = tvg_shape_new();
    $gradient = tvg_linear_gradient_new();
    tvg_gradient_set_color_stops($gradient, tvg_test_stops(), 2);

    expect(tvg_shape_set_gradient($shape, $gradient))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_gradient_get_type($gradient, $t))->toThrow(ValueError::class, 'released');

    tvg_shape_get_gradient($shape, $borrowed);
    tvg_shape_get_gradient($shape, $again);
    expect($borrowed)->toBe($again)
        ->and(fn () => tvg_gradient_del($borrowed))->toThrow(ValueError::class, 'belongs to a shape')
        ->and(fn () => tvg_shape_set_gradient(tvg_shape_new(), $borrowed))->toThrow(ValueError::class, 'duplicate');

    $copy = tvg_gradient_duplicate($borrowed);
    expect(tvg_shape_set_gradient(tvg_shape_new(), $copy))->toBe(TVG_RESULT_SUCCESS);
});

it('releases a borrowed gradient once its shape drops it', function (): void {
    $shape = tvg_shape_new();
    tvg_shape_set_gradient($shape, tvg_linear_gradient_new());
    tvg_shape_get_gradient($shape, $borrowed);
    tvg_shape_set_fill_color($shape, 1, 2, 3, 255);

    expect(fn () => tvg_gradient_get_type($borrowed, $t))->toThrow(ValueError::class, 'no longer holds');
});

it('keeps a shape alive for a borrowed gradient PHP holds', function (): void {
    $gradient = (function () {
        $shape = tvg_shape_new();
        $g = tvg_radial_gradient_new();
        tvg_gradient_set_color_stops($g, tvg_test_stops(), 2);
        tvg_shape_set_stroke_gradient($shape, $g);
        tvg_shape_get_stroke_gradient($shape, $borrowed);

        return $borrowed;
    })();
    gc_collect_cycles();
    tvg_gradient_get_color_stops($gradient, $stops, $count);

    expect($count)->toBe(2);
});

it('deletes a gradient PHP owns', function (): void {
    $gradient = tvg_conic_gradient_new();

    expect(tvg_gradient_del($gradient))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_gradient_del($gradient))->toThrow(ValueError::class, 'released');
});
