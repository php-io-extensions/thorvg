---
type: Runbook
title: Build, install, test
description: Building ext-thorvg on the Mac and Debian, running Pest and the crash sweep, and updating the vendored ThorVG.
resource: config.m4
tags: [thorvg, build]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
---

# Build, install, test

- Mac: `./install-macos.sh` builds into Homebrew `php@8.4` and `php@8.4-zts`. Debian/Pi: `./install-debian-trixie.sh` (needs `build-essential`, `php8.4-dev`).
- ThorVG's C++ compiles through its own make rule in `config.m4` without `$(COMMON_FLAGS)`, so `#include "config.h"` finds `src/thorvg-config/config.h`, not PHP's. Flags follow `src/meson.build` (C++14, `-fno-exceptions -fno-rtti`); NEON is defined on arm64, AVX2 only for `tvgSwRasterSimd.cpp` on x86-64; the AVFoundation media loader (`.mm`, manual retain/release) only on macOS.
- Tests: `php -d memory_limit=128M vendor/bin/pest` on both builds; gate commits on the exit code. Sweep: `php -d memory_limit=256M tools/sweep.php` (950 child processes; `SWEEP_DEBUG=1 php tools/sweep.php --one fn:variant` shows one call).
- New ThorVG: replace `lib/thorvg/` from a tag (`git archive` of `LICENSE README.md CONTRIBUTORS.md inc src`, then remove `src/loaders/lottie`, `src/renderer/gpu_engine`, `src/loaders/external_*`, `src/loaders/media/web`), diff `thorvg_capi.h` and the meson source lists, update stubs, C, tests, `PHP_THORVG_UPSTREAM_COMMIT`, and the version.
