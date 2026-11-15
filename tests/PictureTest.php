<?php

declare(strict_types=1);

const TVG_TEST_SVG = '<svg xmlns="http://www.w3.org/2000/svg" width="8" height="8"><rect id="box" width="8" height="8" fill="#00ff00"/></svg>';

it('loads SVG data and draws it', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $picture = tvg_picture_new();

    expect(tvg_picture_load_data($picture, TVG_TEST_SVG, strlen(TVG_TEST_SVG), 'svg', null, true))->toBe(TVG_RESULT_SUCCESS);
    tvg_picture_get_size($picture, $w, $h);
    tvg_canvas_add($canvas, $picture);
    tvg_test_draw($canvas);

    expect([$w, $h])->toBe([8.0, 8.0])
        ->and(tvg_test_pixel($buffer, 4, 4))->toBe('00ff00ff');
});

it('keeps borrowed SVG bytes alive and checks their size', function (): void {
    $picture = tvg_picture_new();
    $svg = TVG_TEST_SVG.' ';

    expect(tvg_picture_load_data($picture, $svg, strlen(TVG_TEST_SVG), 'svg', null, false))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_picture_load_data(tvg_picture_new(), 'x', 10, 'svg', null, true))->toThrow(ValueError::class, 'must hold 10 bytes');
});

it('loads raw pixels, sized and placed', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $picture = tvg_picture_new();
    $pixels = str_repeat("\xff\x00\x00\xff", 4);

    expect(tvg_picture_load_raw($picture, $pixels, 2, 2, TVG_COLORSPACE_ABGR8888S, true))->toBe(TVG_RESULT_SUCCESS);
    tvg_picture_set_size($picture, 4, 4);
    tvg_picture_set_origin($picture, 0, 0);
    tvg_picture_get_size($picture, $w, $h);
    tvg_picture_set_filter($picture, TVG_FILTER_METHOD_NEAREST);
    tvg_canvas_add($canvas, $picture);
    tvg_test_draw($canvas);

    expect([$w, $h])->toBe([4.0, 4.0])
        ->and(tvg_test_pixel($buffer, 1, 1))->toBe('ff0000ff')
        ->and(fn () => tvg_picture_load_raw(tvg_picture_new(), 'x', 2, 2, TVG_COLORSPACE_ABGR8888S, true))->toThrow(ValueError::class);
});

it('finds a loaded SVG node by id', function (): void {
    $picture = tvg_picture_new();
    tvg_picture_load_data($picture, TVG_TEST_SVG, strlen(TVG_TEST_SVG), 'svg', null, true);
    $node = tvg_picture_get_paint($picture, tvg_accessor_generate_id('box'));

    expect($node)->toBeInstanceOf(Tvg_Paint::class)
        ->and(tvg_picture_get_paint($picture, tvg_accessor_generate_id('missing')))->toBeNull();
});

it('refuses a file outside open_basedir and a missing file', function (): void {
    expect(tvg_picture_load(tvg_picture_new(), '/no/such/file.svg'))->not->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_picture_load(tvg_shape_new(), '/x.svg'))->toThrow(TypeError::class, 'must be a picture');
});

it('composes scenes with effects', function (): void {
    $canvas = tvg_test_canvas($buffer);
    $scene = tvg_scene_new();
    $back = tvg_test_rect(0, 0, 8, 8, [255, 255, 255, 255]);
    tvg_scene_add($scene, $back);
    $front = tvg_test_rect(0, 0, 8, 8, [0, 0, 0, 255]);
    expect(tvg_scene_insert($scene, $front, null))->toBe(TVG_RESULT_INVALID_ARGUMENT)
        ->and(tvg_scene_insert($scene, $front, $back))->toBe(TVG_RESULT_SUCCESS);

    expect(tvg_scene_add_effect_fill($scene, 255, 0, 0, 255))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_scene_add_effect_gaussian_blur($scene, 1.0, 0, 0, 50))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_scene_add_effect_drop_shadow($scene, 0, 0, 0, 128, 45, 2, 1, 50))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_scene_add_effect_tint($scene, 0, 0, 0, 255, 255, 255, 50))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_scene_clear_effects($scene))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_scene_remove($scene, $front))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_scene_add($scene, $scene))->toThrow(ValueError::class);
    tvg_canvas_add($canvas, $scene);
    tvg_test_draw($canvas);

    expect(tvg_test_pixel($buffer, 4, 4))->toBe('ffffffff');
});

it('lays out text in a loaded font', function (): void {
    $font = tvg_test_font_file();
    if ($font === null) {
        $this->markTestSkipped('No TrueType font on this machine.');
    }
    expect(tvg_font_load($font))->toBe(TVG_RESULT_SUCCESS);
    $text = tvg_text_new();
    $name = pathinfo($font, PATHINFO_FILENAME);

    expect(tvg_text_set_font($text, $name))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_text_set_size($text, 12))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_text_set_text($text, 'Hé'))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_text_set_color($text, 1, 2, 3))->toBe(TVG_RESULT_SUCCESS);

    $metrics = new Tvg_Text_Metrics();
    $glyph = new Tvg_Glyph_Metrics();
    expect(tvg_text_get_text_metrics($text, $metrics))->toBe(TVG_RESULT_SUCCESS)
        ->and($metrics->ascent)->toBeGreaterThan(0.0)
        ->and(tvg_text_get_glyph_metrics($text, 'éa', $glyph, $next))->toBe(TVG_RESULT_SUCCESS)
        ->and($next)->toBe(2)
        ->and($glyph->advance)->toBeGreaterThan(0.0)
        ->and($glyph->min)->toBeInstanceOf(Tvg_Point::class)
        ->and(tvg_text_line_count($text))->toBeGreaterThanOrEqual(1)
        ->and(tvg_font_unload($font))->toBe(TVG_RESULT_SUCCESS);
});

it('loads a font from borrowed bytes', function (): void {
    $font = tvg_test_font_file();
    if ($font === null) {
        $this->markTestSkipped('No TrueType font on this machine.');
    }
    $bytes = file_get_contents($font);

    expect(tvg_font_load_data('borrowed', $bytes, strlen($bytes), 'ttf', false))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_font_load_data('x', 'ab', 3, null, true))->toThrow(ValueError::class);
});

it('hands a gradient to text and refuses a non-text paint', function (): void {
    $text = tvg_text_new();
    $gradient = tvg_linear_gradient_new();

    expect(tvg_text_set_gradient($text, $gradient))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_gradient_get_type($gradient, $t))->toThrow(ValueError::class, 'released')
        ->and(fn () => tvg_text_set_size(tvg_shape_new(), 1))->toThrow(TypeError::class, 'must be a text');
});

it('refuses a path that is not valid UTF-8 (the macOS media loader would abort on it)', function (): void {
    expect(fn () => tvg_picture_load(tvg_picture_new(), "\xff.svg"))->toThrow(ValueError::class, 'valid UTF-8')
        ->and(fn () => tvg_font_load("\xff.ttf"))->toThrow(ValueError::class, 'valid UTF-8');
});

it('loads an A8 mask as a picture of black at each alpha', function () {
    tvg_engine_init(0);
    $p = tvg_picture_new();
    expect(tvg_picture_load_alpha($p, "\x00\x80\xff\x40", 2, 2))->toBe(TVG_RESULT_SUCCESS);
    $w = $h = 0.0;
    tvg_picture_get_size($p, $w, $h);
    expect([$w, $h])->toBe([2.0, 2.0]);
    $buf = str_repeat("\0", 16);
    $c = tvg_swcanvas_create(TVG_ENGINE_OPTION_NONE);
    tvg_swcanvas_set_target($c, $buf, 2, 2, 2, TVG_COLORSPACE_ARGB8888);
    tvg_canvas_add($c, $p);
    tvg_canvas_update($c); tvg_canvas_draw($c, true); tvg_canvas_sync($c);
    expect(tvg_swcanvas_get_alpha($buf, 2, 2, 2, TVG_COLORSPACE_ARGB8888))->toBe("\x00\x80\xff\x40");
    expect(fn () => tvg_picture_load_alpha(tvg_picture_new(), "\0", 2, 2))->toThrow(ValueError::class);
    tvg_canvas_destroy($c);
});
