# Log

- 2026-11-13: binding addition `tvg_swcanvas_get_alpha()` (alpha bytes of a 32-bit canvas buffer in one call), for drivers that read coverage out. Pest 50 passed.
- 2026-11-13: crash sweep found 3 failures (font_load abort on invalid UTF-8 via the macOS media loader; two stroker hangs on NaN/INF geometry); both now refused. Pest 49 passed.
- 2026-11-13: ext-thorvg built: ThorVG 1.1.3 vendored without Lottie and GPU engines (Angel's choice), all 190 C API functions bound, Pest 47 passed on php84 NTS + ZTS. Found and worked around the `tvg_paint_get_mask_method` target type error.
