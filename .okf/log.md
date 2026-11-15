# Log

- 2026-11-15: binding addition `tvg_shape_get_stroke_outline(Tvg_Paint, ?array &$cmds, ?int &$cmdsCnt, ?array &$pts, ?int &$ptsCnt): int`, a shape's stroke outline from ThorVG's internal CPU stroker (strokeReset/strokeParseOutline/strokeExportOutline, src/stroke_outline.cpp), before the transform; dash and trim not applied. ThorVG's API has no way to get it. Pest 56 passed on NTS and ZTS; sweep clean.
- 2026-11-15: binding addition `tvg_swcanvas_get_target_address(Tvg_Canvas): int`, the address of the string the canvas draws into (0 for an address target or none), for drivers that lend the canvas's memory. Pest 51 passed on NTS and ZTS.
- 2026-11-13: binding addition `tvg_swcanvas_get_alpha()` (alpha bytes of a 32-bit canvas buffer in one call), for drivers that read coverage out. Pest 50 passed.
- 2026-11-13: crash sweep found 3 failures (font_load abort on invalid UTF-8 via the macOS media loader; two stroker hangs on NaN/INF geometry); both now refused. Pest 49 passed.
- 2026-11-13: ext-thorvg built: ThorVG 1.1.3 vendored without Lottie and GPU engines (Angel's choice), all 190 C API functions bound, Pest 47 passed on php84 NTS + ZTS. Found and worked around the `tvg_paint_get_mask_method` target type error.
* **2026-11-14**: addition `tvg_picture_load_alpha()`, the counterpart of swcanvas_get_alpha: an A8 mask loaded as a 0xCC000000 raw picture, in C.
