<?php

declare(strict_types=1);

it('answers the same object for the same paint', function (): void {
    $scene = tvg_scene_new();
    $shape = tvg_shape_new();
    tvg_scene_add($scene, $shape);

    expect(tvg_paint_get_parent($shape))->toBe($scene)
        ->and(tvg_paint_get_parent($scene))->toBeNull();
});

it('holds one reference per object and refuses to give it back', function (): void {
    $shape = tvg_shape_new();

    expect(tvg_paint_get_ref($shape))->toBe(1)
        ->and(tvg_paint_ref($shape))->toBe(2)
        ->and(tvg_paint_unref($shape, true))->toBe(1)
        ->and(fn () => tvg_paint_unref($shape, true))->toThrow(ValueError::class, 'tvg_paint_ref()')
        ->and(tvg_paint_rel($shape))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_paint_get_ref($shape))->toBe(1);
});

it('transforms, reads the matrix back and bounds', function (): void {
    $shape = tvg_test_rect(0, 0, 10, 10, [0, 0, 0, 255]);
    tvg_paint_translate($shape, 5, 6);
    $m = new Tvg_Matrix();
    tvg_paint_get_transform($shape, $m);
    tvg_paint_get_aabb($shape, $x, $y, $w, $h);
    tvg_paint_get_obb($shape, $corners);

    expect([$m->e11, $m->e13, $m->e23, $m->e33])->toBe([1.0, 5.0, 6.0, 1.0])
        ->and([$x, $y, $w, $h])->toBe([5.0, 6.0, 10.0, 10.0])
        ->and($corners)->toHaveCount(4)
        ->and($corners[0])->toBeInstanceOf(Tvg_Point::class);
});

it('sets opacity, visibility, id and data', function (): void {
    $shape = tvg_shape_new();
    tvg_paint_set_opacity($shape, 77);
    tvg_paint_get_opacity($shape, $opacity);
    tvg_paint_set_visible($shape, false);
    tvg_paint_set_id($shape, 42);
    tvg_paint_set_data($shape, 0x1234);
    tvg_paint_get_type($shape, $type);

    expect($opacity)->toBe(77)
        ->and(tvg_paint_get_visible($shape))->toBeFalse()
        ->and(tvg_paint_get_id($shape))->toBe(42)
        ->and(tvg_paint_get_data($shape))->toBe(0x1234)
        ->and($type)->toBe(TVG_TYPE_SHAPE)
        ->and(fn () => tvg_paint_set_opacity($shape, 256))->toThrow(ValueError::class);
});

it('clips to a shape and refuses other clippers', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $fill = tvg_test_rect(0, 0, 8, 8, [255, 0, 0, 255]);
    $clip = tvg_shape_new();
    tvg_shape_append_rect($clip, 0, 0, 4, 8, 0, 0, true);
    expect(tvg_paint_set_clip($fill, $clip))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_paint_get_clip($fill))->toBe($clip);
    tvg_canvas_add($canvas, $fill);
    tvg_test_draw($canvas);

    expect(tvg_test_pixel($buffer, 1, 1))->toBe('ff0000ff')
        ->and(tvg_test_pixel($buffer, 6, 1))->toBe('00000000')
        ->and(fn () => tvg_paint_set_clip($fill, tvg_scene_new()))->toThrow(TypeError::class, 'must be a shape')
        ->and(fn () => tvg_paint_set_clip($fill, $fill))->toThrow(ValueError::class);
});

it('masks with alpha and refuses a missing target', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $fill = tvg_test_rect(0, 0, 8, 8, [0, 255, 0, 255]);
    $mask = tvg_test_rect(4, 0, 4, 8, [255, 255, 255, 255]);
    tvg_paint_set_mask_method($fill, $mask, TVG_MASK_METHOD_ALPHA);
    tvg_paint_get_mask_method($fill, $target, $method);
    tvg_canvas_add($canvas, $fill);
    tvg_test_draw($canvas);

    expect($method)->toBe(TVG_MASK_METHOD_ALPHA)
        ->and($target)->toBe($mask)
        ->and(tvg_test_pixel($buffer, 6, 1))->toBe('00ff00ff')
        ->and(tvg_test_pixel($buffer, 1, 1))->toBe('00000000')
        ->and(fn () => tvg_paint_set_mask_method($fill, null, TVG_MASK_METHOD_ALPHA))->toThrow(ValueError::class)
        ->and(fn () => tvg_paint_set_mask_method($fill, $mask, 99))->toThrow(ValueError::class);
});

it('duplicates and blends', function (): void {
    $shape = tvg_test_rect(0, 0, 1, 1, [1, 2, 3, 4]);
    $copy = tvg_paint_duplicate($shape);
    tvg_shape_get_fill_color($copy, $r, $g, $b, $a);

    expect($copy)->not->toBe($shape)
        ->and([$r, $g, $b, $a])->toBe([1, 2, 3, 4])
        ->and(tvg_paint_set_blend_method($shape, TVG_BLEND_METHOD_MULTIPLY))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_paint_set_blend_method($shape, 40))->toThrow(ValueError::class);
});

it('tests intersection once the paint is in an updated canvas', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $shape = tvg_test_rect(0, 0, 4, 4, [0, 0, 0, 255]);
    expect(tvg_paint_intersects($shape, 1, 1, 1, 1))->toBeFalse();
    tvg_canvas_add($canvas, $shape);
    tvg_canvas_update($canvas);

    expect(tvg_paint_intersects($shape, 1, 1, 1, 1))->toBeTrue()
        ->and(tvg_paint_intersects($shape, 10, 10, 1, 1))->toBeFalse();
});
