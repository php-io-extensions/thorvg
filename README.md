<div align="center" id="header">

<h1>ext-thorvg</h1>

<h3>ThorVG 1.1.3's C API bound 1:1 into PHP 8.4+, with the library compiled in</h3>


[![CI](https://img.shields.io/github/actions/workflow/status/php-io-extensions/thorvg/ci.yml?style=flat-square&label=CI)](https://github.com/php-io-extensions/thorvg/actions/workflows/ci.yml)
[![Packagist](https://img.shields.io/packagist/v/php-io-extensions/thorvg?style=flat-square)](https://packagist.org/packages/php-io-extensions/thorvg)
[![PHP](https://img.shields.io/packagist/dependency-v/php-io-extensions/thorvg/php?style=flat-square&label=PHP)](https://packagist.org/packages/php-io-extensions/thorvg)
[![License](https://img.shields.io/github/license/php-io-extensions/thorvg?style=flat-square)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-linux_%7C_macos-blue?style=flat-square&logo=linux&logoColor=white)](https://github.com/thorvg/thorvg)
[![PIE](https://img.shields.io/badge/PIE-installable-4f5b93?style=flat-square&logo=php&logoColor=white)](https://github.com/php/pie)

</div>

A 2D scene in software is more than filled paths: shapes with strokes, dashes and trims, linear, radial and conic gradients, scenes that group paints and blur, shadow or tint them, alpha and luma masks, blend modes, pictures loaded from SVG, PNG, JPG or WebP, text laid out from a TrueType or OpenType font, and frames saved as an animated GIF.

<b>ThorVG</b> does all of that in one engine: a retained scene of reference-counted paints rendered by a SIMD CPU rasteriser (NEON on ARM, AVX2 on x86-64) on its own worker threads, with partial redraw, into 32-bit pixels with straight or premultiplied alpha.

<b>The only problem?</b> PHP can't reach it. This extension binds every function of ThorVG's C API (`thorvg_capi.h`) one to one under the C names, with ThorVG compiled into the module from an unchanged copy of the upstream tag, so there is nothing to install from the system. Handles are objects that keep what ThorVG still uses alive, structs are typed classes, and every argument ThorVG would trust blindly is checked first. No defaults, no composites, no opinions: what ThorVG documents is what you call.

## Basic usage

```php
<?php
// A red rounded square under a translucent blue disc, drawn into a 64×64 RGBA string.
tvg_engine_init(0);

$pixels = str_repeat("\0", 64 * 64 * 4);
$canvas = tvg_swcanvas_create(TVG_ENGINE_OPTION_DEFAULT);
tvg_swcanvas_set_target($canvas, $pixels, 64, 64, 64, TVG_COLORSPACE_ABGR8888S); // straight RGBA bytes

$square = tvg_shape_new();
tvg_shape_append_rect($square, 8, 8, 48, 48, 6, 6, true);
tvg_shape_set_fill_color($square, 220, 40, 40, 255);

$disc = tvg_shape_new();
tvg_shape_append_circle($disc, 40, 40, 16, 16, true);
tvg_shape_set_fill_color($disc, 30, 90, 230, 160);

tvg_canvas_add($canvas, $square);
tvg_canvas_add($canvas, $disc);
tvg_canvas_draw($canvas, true);
tvg_canvas_sync($canvas); // drawing may run on worker threads: read pixels after sync

echo bin2hex(substr($pixels, (20 * 64 + 20) * 4, 4)), "\n"; // dc2828ff
echo bin2hex(substr($pixels, (40 * 64 + 40) * 4, 4)), "\n"; // 64479efe
```

## Requirements

- PHP 8.4 or newer, NTS or ZTS, with `phpize` and `php-config`.
- A C and C++ compiler.
- No system libraries. On macOS the media loader links AVFoundation, which ships with the system.

```bash
# Debian, Ubuntu, Raspberry Pi OS
sudo apt install build-essential php8.4-dev

# macOS: Xcode Command Line Tools, and Homebrew's PHP ships phpize and php-config
xcode-select --install
```

## Installation

### With PHP PIE (recommended)

```bash
pie install php-io-extensions/thorvg
```

### Manually (install script)

```bash
git clone https://github.com/php-io-extensions/thorvg.git
cd thorvg

./install-debian-trixie.sh             # Debian Trixie, Ubuntu 24.04+, Raspberry Pi OS: the php on PATH
./install-macos.sh                     # Homebrew php@8.4 and php@8.4-zts
./install-macos.sh /path/to/bin/php    # either script takes specific PHP binaries
```

### Manually (phpize)

```bash
git clone https://github.com/php-io-extensions/thorvg.git
cd thorvg
phpize
./configure --enable-thorvg
make -j"$(nproc 2>/dev/null || sysctl -n hw.ncpu)"
sudo make install
```

Then add `extension=thorvg.so` to your `php.ini`, or to a file in the scan directory `php --ini` reports.

### Verify

```console
$ php --ri thorvg

thorvg

thorvg support => enabled
Version => 0.11.x
ThorVG version => 1.1.3
ThorVG commit => 589bc4120f2097fb1b135e552c2ef39f6581612b
ThorVG modules => cpu engine, svg, png, jpg, webp, ttf, otf, media, gif saver
```

## API

All 190 functions of ThorVG's C API, under their C names, plus one binding addition: `tvg_swcanvas_get_alpha()` returns the alpha byte of every pixel of a 32-bit canvas buffer in one call (a shape drawn in opaque white on a cleared buffer leaves its coverage there). The full rules are in the [design spec](docs/superpowers/specs/2026-11-13-thorvg-design.md).

### What is compiled in

The CPU engine (partial rendering, task scheduler, NEON or AVX2), the SVG, PNG, JPG, WebP and TTF/OTF loaders, the media loader (AVFoundation on macOS; no backend elsewhere, so `tvg_video_*` load nothing on Linux), and the GIF saver. **Not** compiled in: the GL and WebGPU engines and the Lottie loader. Their functions are still bound and answer what ThorVG answers without them: `tvg_glcanvas_create()`, `tvg_wgcanvas_create()` and `tvg_lottie_animation_new()` return `null`, the rest `TVG_RESULT_NOT_SUPPORTED`.

### Translations

- **Constants:** every enum value (`TVG_RESULT_*`, `TVG_COLORSPACE_*`, `TVG_BLEND_METHOD_*`, `TVG_PATH_COMMAND_*`, …).
- **Handles** (`Tvg_Canvas`, `Tvg_Paint`, `Tvg_Gradient`, `Tvg_Saver`, `Tvg_Animation`, `Tvg_Accessor`, `Tvg_Video`) are final classes. A C `NULL` is `null`. The same paint or gradient always comes back as the same object. `*_del` and `tvg_canvas_destroy` release a handle early; a released handle throws `ValueError`.
- **Value structs** (`Tvg_Point`, `Tvg_Matrix`, `Tvg_Region`, `Tvg_Color_Stop`, `Tvg_Text_Metrics`, `Tvg_Glyph_Metrics`, `Tvg_WgContext`, `Tvg_Audio_Info`) have one typed property per C field, zero by default. A struct ThorVG fills (`tvg_paint_get_transform`, `tvg_text_get_text_metrics`) is written into the object you pass.
- **Out-parameters** are references (`tvg_paint_get_aabb($paint, $x, $y, $w, $h)`); arrays ThorVG hands back (`tvg_shape_get_path`, `tvg_gradient_get_color_stops`, `tvg_canvas_get_dirty_regions`, `tvg_paint_get_obb`) are lists by reference.
- **Lists** stand for a pointer and count; the count stays its own argument and may not exceed the list.
- **Memory:** `tvg_swcanvas_set_target`'s buffer is a string ThorVG draws into in place (build it at run time, e.g. `str_repeat()`; a literal is refused) or an address. `tvg_picture_load_raw`, `tvg_picture_load_data` and `tvg_font_load_data` take a string or an address; without `copy`, a string stays alive until the request ends. `void*` arguments are addresses.
- **`tvg_text_get_glyph_metrics`'s `next`** is the byte offset of the next character in `$ch`.
- **`tvg_paint_get_mask_method`'s `target`** is a reference you receive the mask target in: the header types it as a paint but documents it `[out]`, and ThorVG writes through it.

### Lifetimes

Paints are reference-counted: each `Tvg_Paint` object holds one reference, so a paint you drop lives on in the canvas or scene it was added to, and one you hold outlives them. `tvg_paint_ref`/`tvg_paint_unref` adjust ThorVG's count, but `unref` cannot give back the object's own reference. Setting a gradient hands it to the shape or text: its object is released. `tvg_shape_get_gradient` and `tvg_shape_get_stroke_gradient` lend the shape's gradient back; a lent gradient throws once the shape no longer holds it, and cannot be deleted or set elsewhere (`tvg_gradient_duplicate` it). A canvas keeps its target string and finishes a draw before it is destroyed; a saver keeps the animation it renders until `tvg_saver_sync`.

### Callbacks

`tvg_accessor_set` takes `callable(Tvg_Paint $paint, mixed $data): bool` and calls it synchronously for each paint; returning false or throwing stops the walk. The asset and audio resolvers take a callable or `null`; only the Lottie loader calls them, which this build does not have.

### Errors

ThorVG reports failure through `TVG_RESULT_*` values, which come back as ints. Arguments ThorVG would trust and crash on are refused before it runs: a paint of the wrong type for a `tvg_shape_*`, `tvg_scene_*`, `tvg_picture_*` or `tvg_text_*` function (`TypeError`), and an enum or channel out of range, a short buffer, a count past its list, a negative or NaN dash, a mask or clip on the paint itself, NaN or infinite path coordinates (ThorVG's stroker can loop forever on them), or a file path that is not valid UTF-8 (ThorVG's macOS media loader aborts on one) (`ValueError`). Paths outside `open_basedir` answer `TVG_RESULT_INVALID_ARGUMENT`.

## Running the test suite

```bash
composer install
php -d memory_limit=128M vendor/bin/pest
php -d memory_limit=256M tools/sweep.php   # crash sweep: every function, five argument sets, one process each
```

The text tests use a TrueType font found on the machine (Arial on macOS, DejaVu Sans on Debian) and skip without one.

## Security

See [SECURITY.md](SECURITY.md). Images, SVG and fonts are trusted input.

## License

MIT for this extension. ThorVG is MIT, [lib/thorvg/LICENSE](lib/thorvg/LICENSE).
