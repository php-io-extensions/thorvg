<?php

declare(strict_types=1);

it('builds and reads back a path', function (): void {
    $shape = tvg_shape_new();
    tvg_shape_move_to($shape, 0, 0);
    tvg_shape_line_to($shape, 4, 0);
    tvg_shape_cubic_to($shape, 4, 2, 2, 4, 0, 4);
    tvg_shape_close($shape);
    tvg_shape_get_path($shape, $cmds, $cmdCount, $points, $pointCount);

    expect($cmds)->toBe([TVG_PATH_COMMAND_MOVE_TO, TVG_PATH_COMMAND_LINE_TO, TVG_PATH_COMMAND_CUBIC_TO, TVG_PATH_COMMAND_CLOSE])
        ->and($cmdCount)->toBe(4)
        ->and($pointCount)->toBe(5)
        ->and([$points[4]->x, $points[4]->y])->toBe([0.0, 4.0]);
});

it('appends a path from lists and checks the counts', function (): void {
    $shape = tvg_shape_new();
    $cmds = [TVG_PATH_COMMAND_MOVE_TO, TVG_PATH_COMMAND_LINE_TO];
    $points = [new Tvg_Point(1, 2), new Tvg_Point(3, 4)];

    expect(tvg_shape_append_path($shape, $cmds, 2, $points, 2))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_shape_append_path($shape, $cmds, 3, $points, 2))->toThrow(ValueError::class, 'count of 3')
        ->and(fn () => tvg_shape_append_path($shape, [9], 1, $points, 2))->toThrow(ValueError::class, 'TVG_PATH_COMMAND_')
        ->and(fn () => tvg_shape_append_path($shape, $cmds, 2, [1, 2], 2))->toThrow(TypeError::class, 'Tvg_Point');
});

it('strokes with width, colour, cap, join, miter and dash', function (): void {
    $shape = tvg_shape_new();
    tvg_shape_set_stroke_width($shape, 3);
    tvg_shape_set_stroke_color($shape, 10, 20, 30, 40);
    tvg_shape_set_stroke_cap($shape, TVG_STROKE_CAP_ROUND);
    tvg_shape_set_stroke_join($shape, TVG_STROKE_JOIN_BEVEL);
    tvg_shape_set_stroke_miterlimit($shape, 7);
    tvg_shape_set_stroke_dash($shape, [2.0, 1.0], 2, 0.5);
    tvg_shape_get_stroke_width($shape, $width);
    tvg_shape_get_stroke_color($shape, $r, $g, $b, $a);
    tvg_shape_get_stroke_cap($shape, $cap);
    tvg_shape_get_stroke_join($shape, $join);
    tvg_shape_get_stroke_miterlimit($shape, $miter);
    tvg_shape_get_stroke_dash($shape, $dash, $count, $offset);

    expect([$width, $r, $g, $b, $a, $cap, $join, $miter])->toBe([3.0, 10, 20, 30, 40, TVG_STROKE_CAP_ROUND, TVG_STROKE_JOIN_BEVEL, 7.0])
        ->and([$dash, $count, $offset])->toBe([[2.0, 1.0], 2, 0.5])
        ->and(fn () => tvg_shape_set_stroke_dash($shape, [-1.0], 1, 0))->toThrow(ValueError::class, 'non-negative')
        ->and(fn () => tvg_shape_set_stroke_dash($shape, [NAN], 1, 0))->toThrow(ValueError::class)
        ->and(tvg_shape_set_stroke_dash($shape, null, 0, 0))->toBe(TVG_RESULT_SUCCESS);
});

it('fills with a rule and a solid colour', function (): void {
    $shape = tvg_shape_new();
    tvg_shape_set_fill_rule($shape, TVG_FILL_RULE_EVEN_ODD);
    tvg_shape_get_fill_rule($shape, $rule);
    tvg_shape_set_fill_color($shape, 5, 6, 7, 8);
    tvg_shape_get_fill_color($shape, $r, $g, $b, $a);

    expect($rule)->toBe(TVG_FILL_RULE_EVEN_ODD)
        ->and([$r, $g, $b, $a])->toBe([5, 6, 7, 8])
        ->and(fn () => tvg_shape_set_fill_color($shape, 256, 0, 0, 0))->toThrow(ValueError::class);
});

it('refuses a paint that is not a shape', function (): void {
    expect(fn () => tvg_shape_append_rect(tvg_scene_new(), 0, 0, 1, 1, 0, 0, true))->toThrow(TypeError::class, 'must be a shape, a scene given')
        ->and(fn () => tvg_shape_set_fill_color(tvg_text_new(), 0, 0, 0, 0))->toThrow(TypeError::class, 'a text given');
});

it('draws a circle and a trimmed path', function (): void {
    $canvas = tvg_test_canvas($buffer, 16, 16);
    $circle = tvg_shape_new();
    tvg_shape_append_circle($circle, 8, 8, 6, 6, true);
    tvg_shape_set_fill_color($circle, 0, 0, 255, 255);
    tvg_shape_set_trimpath($circle, 0, 1, false);
    tvg_canvas_add($canvas, $circle);
    tvg_test_draw($canvas);

    expect(tvg_test_pixel($buffer, 8, 8, 16))->toBe('0000ffff')
        ->and(tvg_test_pixel($buffer, 0, 0, 16))->toBe('00000000');
});

it('resets a shape', function (): void {
    $shape = tvg_test_rect(0, 0, 1, 1, [1, 1, 1, 1]);
    tvg_shape_reset($shape);
    tvg_shape_get_path($shape, $cmds, $count, $points, $pointCount);

    expect($count)->toBe(0)->and($cmds)->toBe([]);
});

it('refuses NaN and infinite path geometry, on which ThorVG\'s stroker never finishes', function (): void {
    $shape = tvg_shape_new();

    expect(fn () => tvg_shape_append_circle($shape, 5, 5, NAN, 5, true))->toThrow(ValueError::class, 'must be finite')
        ->and(fn () => tvg_shape_move_to($shape, 0, INF))->toThrow(ValueError::class, 'Argument #3')
        ->and(fn () => tvg_shape_cubic_to($shape, 0, 0, 0, 0, -INF, 0))->toThrow(ValueError::class)
        ->and(fn () => tvg_shape_append_rect($shape, 0, 0, NAN, 1, 0, 0, true))->toThrow(ValueError::class)
        ->and(fn () => tvg_shape_append_path($shape, [TVG_PATH_COMMAND_MOVE_TO], 1, [new Tvg_Point(NAN, 0)], 1))->toThrow(ValueError::class, 'finite points')
        ->and(tvg_shape_move_to($shape, 1e30, -1e30))->toBe(TVG_RESULT_SUCCESS);
});
