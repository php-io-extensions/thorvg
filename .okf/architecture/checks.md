---
type: Architecture
title: Safety checks
description: Inputs ThorVG 1.1.3 trusts that the binding refuses, an upstream type error, symbol export.
resource: src/runtime.c
tags: [thorvg, security]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
---

# Safety checks

- Paint type checked before every `tvg_shape_*`, `tvg_scene_*`, `tvg_picture_*`, `tvg_text_*` call and for clippers (ThorVG `reinterpret_cast`s); gradient type before the linear/radial/conic setters and getters.
- Enums, `uint8_t` channels and `uint32_t`/`int32_t` ranges checked; colorspaces 0..6 or 255; blend methods 0..16 or 255.
- Buffers: stride × h × 4 for canvas targets (interned strings refused: ThorVG writes in place), w × h × 4 for raw pictures, `size` for data.
- Lists: count ≤ length; path commands 0..3; dash lengths finite and non-negative.
- Path coordinates (move/line/cubic/rect/circle/append_path points) must be finite: the sweep found the stroker never finishing on NaN/INF geometry.
- `tvg_picture_load`/`tvg_font_load` paths must be valid UTF-8: on macOS ThorVG tries the AVFoundation media loader, which aborts the process (`NSURL` nil-string exception) on invalid UTF-8.
- Mask and clip on the paint itself, a mask target missing for a non-None method, a scene added to itself: refused.
- `tvg_paint_get_mask_method`: the header types `target` as `const Tvg_Paint` but ThorVG writes the mask target through it; passing a paint overwrote its vtable (found by the suite). The binding passes a local.
- File paths and `rpath` through `open_basedir`; paths inside an SVG are not (documented in SECURITY.md).
- Only `get_module` is exported (`-exported_symbol` on macOS, `src/thorvg.map` on Linux).
- `tools/sweep.php`: every function × five argument sets, one process each, with each paint type and released handles.
