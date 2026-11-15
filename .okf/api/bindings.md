---
type: API
title: Bindings
description: All 190 functions of ThorVG 1.1.3's C API under their C names, the classes, the translations, and which modules are compiled in.
resource: stubs/
tags: [thorvg, api]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
---

# Bindings

- Every `TVG_API` function of `lib/thorvg/src/bindings/capi/thorvg_capi.h`, declared in `stubs/thorvg_{core,canvas,paint,shape,gradient,picture,misc}.stub.php`, one hand-written `ZEND_FUNCTION` each in `src/{thorvg,canvas,paint,shape,gradient,picture,misc}.c`. Three additions: `tvg_shape_get_stroke_outline(Tvg_Paint $paint, ?array &$cmds, ?int &$cmdsCnt, ?array &$pts, ?int &$ptsCnt): int` (`src/shape.c`, `src/stroke_outline.cpp`), the stroke's outline from ThorVG's internal CPU stroker in the shape's own coordinates, dash and trim not applied, empty with no stroke width; `tvg_swcanvas_get_target_address(Tvg_Canvas $canvas): int` (`src/canvas.c`), the address of the string kept as the canvas's target, 0 when the target was an address or none is set; and `tvg_swcanvas_get_alpha(string|int $buffer, $stride, $w, $h, $cs): string` (`src/canvas.c`), the alpha byte of each pixel of a 32-bit canvas buffer, rows packed; refuses a width above the stride, a short string, address 0 and non-32-bit colorspaces.
- Constants: every enum value plus `TVG_PATH_COMMAND_*` (`stubs/thorvg_constants.stub.php`, 80).
- Handles (`stubs/thorvg_types.stub.php`): `Tvg_Canvas`, `Tvg_Paint`, `Tvg_Gradient`, `Tvg_Saver`, `Tvg_Animation`, `Tvg_Accessor`, `Tvg_Video`. Structs: `Tvg_Point`, `Tvg_Matrix`, `Tvg_Region`, `Tvg_Color_Stop`, `Tvg_Text_Metrics`, `Tvg_Glyph_Metrics`, `Tvg_WgContext`, `Tvg_Audio_Info`.
- Translations: out-parameters by reference; pointer + count as a list + count (count ≤ length); output arrays as lists by reference; `string|int` memory (string kept or borrowed, int address trusted); `void*` as an address; glyph `next` as a byte offset; `tvg_paint_get_mask_method`'s `target` as the out-parameter its documentation says (the header's type is wrong).
- Modules in (`src/thorvg-config/config.h`): CPU engine, partial render, threads, SVG, PNG, JPG, WebP, TTF/OTF, media (AVFoundation on macOS only), GIF saver, C API, file IO. Out (Angel, 2026-11-13): GL, WebGPU, Lottie; their 21 functions answer `null` or `TVG_RESULT_NOT_SUPPORTED`.
- The GIF saver saves animations only; `tvg_saver_save_paint` always fails in this build (no `.tvg` saver in 1.1.3).
- `tvg_scene_insert` and `tvg_canvas_insert` need a non-null `at` (ThorVG answers `INVALID_ARGUMENT` for null); `tvg_paint_intersects` answers false until the paint is in an updated canvas.
