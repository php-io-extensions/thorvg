<?php

declare(strict_types=1);

it('walks a scene with an accessor and stops when told', function (): void {
    $scene = tvg_scene_new();
    tvg_scene_add($scene, tvg_shape_new());
    tvg_scene_add($scene, tvg_shape_new());
    $accessor = tvg_accessor_new();
    $seen = [];
    tvg_accessor_set($accessor, $scene, function (Tvg_Paint $paint, mixed $data) use (&$seen): bool {
        $seen[] = $data;

        return true;
    }, 'tag');
    $stopped = 0;
    tvg_accessor_set($accessor, $scene, function () use (&$stopped): bool {
        $stopped++;

        return false;
    }, null);

    expect($seen)->toBe(['tag', 'tag', 'tag'])
        ->and($stopped)->toBe(1)
        ->and(tvg_accessor_generate_id('box'))->toBe(tvg_accessor_generate_id('box'))
        ->and(tvg_accessor_del($accessor))->toBe(TVG_RESULT_SUCCESS)
        ->and(fn () => tvg_accessor_del($accessor))->toThrow(ValueError::class);
});

it('lets an exception in the accessor callback through', function (): void {
    $scene = tvg_scene_new();
    tvg_scene_add($scene, tvg_shape_new());

    expect(fn () => tvg_accessor_set(tvg_accessor_new(), $scene, fn () => throw new RuntimeException('stop'), null))->toThrow(RuntimeException::class, 'stop');
});

it('holds an animation and its picture', function (): void {
    $animation = tvg_animation_new();
    $picture = tvg_animation_get_picture($animation);
    tvg_animation_get_total_frame($animation, $frames);

    expect($picture)->toBeInstanceOf(Tvg_Paint::class)
        ->and($frames)->toBe(0.0)
        ->and(tvg_animation_set_frame($animation, 1))->not->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_animation_del($animation))->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_paint_get_ref($picture))->toBe(1);
});

it('saves only animations, and refuses an empty one', function (): void {
    $saver = tvg_saver_new();
    $file = sys_get_temp_dir().'/thorvg-test.gif';

    expect(tvg_saver_save_paint($saver, tvg_shape_new(), $file, 100))->not->toBe(TVG_RESULT_SUCCESS)
        ->and(tvg_saver_save_animation($saver, tvg_animation_new(), $file, 100, 30))->toBe(TVG_RESULT_INSUFFICIENT_CONDITION)
        ->and(tvg_saver_sync($saver))->toBe(TVG_RESULT_INSUFFICIENT_CONDITION)
        ->and(tvg_saver_del($saver))->toBe(TVG_RESULT_SUCCESS);
});

it('has no Lottie loader in this build', function (): void {
    expect(tvg_lottie_animation_new())->toBeNull()
        ->and(tvg_lottie_animation_expressions_supported())->toBeFalse()
        ->and(tvg_lottie_animation_set_quality(tvg_animation_new(), 50))->toBe(TVG_RESULT_NOT_SUPPORTED);
});

it('creates a video handle whose picture is a paint', function (): void {
    $video = tvg_video_new();
    if ($video === null) {
        $this->markTestSkipped('No media backend on this platform.');
    }

    expect(tvg_video_get_picture($video))->toBeInstanceOf(Tvg_Paint::class)
        ->and(tvg_video_set_loop($video, true))->toBeInt()
        ->and(tvg_video_get_duration($video))->toBe(0.0)
        ->and(tvg_video_del($video))->toBe(TVG_RESULT_SUCCESS);
});
