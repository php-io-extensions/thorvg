<?php

/*
 * Crash sweep: calls every tvg_* function with argument sets built from its signature,
 * each call in its own child process. A PHP exception or a ThorVG error result is a
 * pass; a signal (segfault, SIGFPE, abort) or a hang is a failure. Run after any change
 * to argument checks:  php -d memory_limit=256M tools/sweep.php
 *
 * A string|int memory argument only ever gets strings: an address is trusted by design.
 * Children run in a scratch directory: the file-writing functions get junk names.
 */

declare(strict_types=1);

const SWEEP_SVG = '<svg xmlns="http://www.w3.org/2000/svg" width="8" height="8"><g id="g"><rect id="r" width="8" height="8" fill="#0f0" stroke="#f00" stroke-dasharray="0.001"/></g></svg>';

if ($argc > 2 && $argv[1] === '--one') {
    $at = strrpos($argv[2], ':');
    $name = substr($argv[2], 0, $at);
    $variant = (int) substr($argv[2], $at + 1);
    tvg_engine_init($variant % 2);
    $f = new ReflectionFunction($name);
    $args = [];
    foreach ($f->getParameters() as $p) {
        $args[] = sweep_value($p, $variant);
    }
    try {
        $result = $f->invokeArgs($args);
        if (getenv('SWEEP_DEBUG')) {
            echo 'returned ', var_export($result, true), "\n";
        }
        // Draw whatever the call left behind, so a bad state crashes here rather than hiding.
        foreach ($args as $arg) {
            if ($arg instanceof Tvg_Paint) {
                sweep_draw($arg);
            }
        }
    } catch (Throwable $e) {
        if (getenv('SWEEP_DEBUG')) {
            echo get_class($e), ': ', $e->getMessage(), "\n";
        }
    }
    exit(0);
}

function sweep_value(ReflectionParameter $p, int $v): mixed
{
    $type = $p->getType();
    $name = $type instanceof ReflectionNamedType ? $type->getName() : 'string';
    return match ($name) {
        'int' => [0, -1, 1 << 20, PHP_INT_MAX, 7][$v],
        'float' => [0.0, -1.0, 1e9, INF, NAN][$v],
        'bool' => $v % 2 === 1,
        'string' => ['', "\xff", str_repeat("\x01", 64), str_repeat("\0", 4096), SWEEP_SVG][$v],
        'array' => [[], [0], [1, 2, 3], array_fill(0, 9, 1 << 16), [new Tvg_Point(NAN, INF), new Tvg_Color_Stop(2.0, 1, 2, 3, 4)]][$v],
        'callable' => fn (...$a) => true,
        'mixed' => null,
        'Tvg_Canvas' => sweep_canvas($v),
        'Tvg_Paint' => sweep_paint($v),
        'Tvg_Gradient' => sweep_gradient($v),
        'Tvg_Saver' => sweep_released(tvg_saver_new(), 'tvg_saver_del', $v),
        'Tvg_Animation' => sweep_released(tvg_animation_new(), 'tvg_animation_del', $v),
        'Tvg_Accessor' => sweep_released(tvg_accessor_new(), 'tvg_accessor_del', $v),
        'Tvg_Video' => tvg_video_new() ?? sweep_released(tvg_animation_new(), 'tvg_animation_del', 0),
        default => class_exists($name) ? sweep_struct($name, $v) : null,
    };
}

function sweep_released(object $handle, string $del, int $v): object
{
    if ($v === 3) {
        $del($handle);
    }

    return $handle;
}

function sweep_canvas(int $v): Tvg_Canvas
{
    static $buffers = [];
    $c = tvg_swcanvas_create($v === 4 ? TVG_ENGINE_OPTION_SMART_RENDER : TVG_ENGINE_OPTION_DEFAULT);
    if ($v !== 1) {
        $buffers[] = $b = str_repeat("\0", 16 * 16 * 4);
        tvg_swcanvas_set_target($c, $b, 16, 16, 16, TVG_COLORSPACE_ABGR8888S);
        tvg_canvas_add($c, sweep_paint(0));
    }
    if ($v === 2) {
        tvg_canvas_draw($c, true);
    }
    if ($v === 3) {
        tvg_canvas_destroy($c);
    }

    return $c;
}

function sweep_paint(int $v): Tvg_Paint
{
    switch ($v) {
        case 0:
            $s = tvg_shape_new();
            tvg_shape_append_rect($s, 1, 1, 6, 6, 2, 2, true);
            tvg_shape_set_fill_color($s, 255, 0, 0, 200);
            return $s;
        case 1:
            $scene = tvg_scene_new();
            tvg_scene_add($scene, sweep_paint(0));
            tvg_scene_add_effect_gaussian_blur($scene, 2, 0, 0, 50);
            return $scene;
        case 2:
            $p = tvg_picture_new();
            tvg_picture_load_data($p, SWEEP_SVG, strlen(SWEEP_SVG), 'svg', null, true);
            return $p;
        case 3:
            $t = tvg_text_new();
            tvg_text_set_text($t, "Hé\u{1F600}");
            tvg_text_set_size($t, 1e9);
            return $t;
        default:
            $s = tvg_shape_new();
            tvg_shape_move_to($s, -1e30, 1e30);
            tvg_shape_cubic_to($s, 1e30, -1e30, 0, 0, 1, 1);
            tvg_shape_set_stroke_width($s, 1e9);
            tvg_shape_set_stroke_dash($s, [0.0, 0.0], 2, 0);
            return $s;
    }
}

function sweep_gradient(int $v): Tvg_Gradient
{
    $g = [tvg_linear_gradient_new(), tvg_radial_gradient_new(), tvg_conic_gradient_new(), tvg_linear_gradient_new(), tvg_radial_gradient_new()][$v];
    tvg_gradient_set_color_stops($g, [new Tvg_Color_Stop(0, 1, 2, 3, 4), new Tvg_Color_Stop(NAN, 5, 6, 7, 8)], 2);
    if ($v === 3) {
        tvg_gradient_del($g);
    }
    if ($v === 4) {
        $s = tvg_shape_new();
        tvg_shape_set_gradient($s, $g);
        tvg_shape_get_gradient($s, $g);
    }

    return $g;
}

function sweep_draw(Tvg_Paint $paint): void
{
    static $buffer;
    $buffer = str_repeat("\0", 32 * 32 * 4);
    $c = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);
    tvg_swcanvas_set_target($c, $buffer, 32, 32, 32, TVG_COLORSPACE_ABGR8888S);
    if (tvg_paint_get_parent($paint) === null) {
        tvg_canvas_add($c, $paint);
    }
    tvg_canvas_draw($c, true);
    tvg_canvas_sync($c);
}

function sweep_struct(string $class, int $v): object
{
    $o = new $class();
    if ($v === 0) {
        return $o;
    }
    foreach ((new ReflectionClass($o))->getProperties() as $prop) {
        $t = $prop->getType()?->getName();
        if ($t === 'int') {
            $prop->setValue($o, [0, -1, 1 << 20, 0x7fffffff, 3][$v]);
        } elseif ($t === 'float') {
            $prop->setValue($o, [0.0, -1.0, 1e9, INF, NAN][$v]);
        }
    }

    return $o;
}

$fails = [];
$functions = get_extension_funcs('thorvg');
$cwd = sys_get_temp_dir() . '/thorvg-sweep-' . getmypid();
@mkdir($cwd);
sort($functions);
foreach ($functions as $fn) {
    for ($variant = 0; $variant < 5; $variant++) {
        $p = proc_open([PHP_BINARY, '-d', 'memory_limit=256M', __FILE__, '--one', "$fn:$variant"], [1 => ['file', '/dev/null', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, $cwd);
        $start = microtime(true);
        while (($s = proc_get_status($p))['running'] && microtime(true) - $start < 10) {
            usleep(2000);
        }
        if ($s['running']) {
            proc_terminate($p, 9);
            $fails[] = "$fn:$variant hang";
        } elseif ($s['signaled'] || $s['exitcode'] !== 0) {
            $fails[] = "$fn:$variant " . ($s['signaled'] ? 'signal ' . $s['termsig'] : 'exit ' . $s['exitcode']);
        }
        proc_close($p);
    }
}
echo count($functions) * 5, ' calls, ', count($fails), " failures\n", implode("\n", $fails), "\n";
array_map('unlink', glob($cwd . '/{,.}*[!.]*', GLOB_BRACE) ?: []);
@rmdir($cwd);
exit($fails === [] ? 0 : 1);
