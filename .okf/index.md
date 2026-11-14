---
okf_version: "0.2"
---

# ext-thorvg

1:1 PHP bindings of ThorVG 1.1.3's C API (vendored, unchanged; Lottie and GPU engines not compiled), a 2D vector graphics engine. Version 0.11.0. Linux, macOS. PHP 8.4 NTS + ZTS.

# API

* [Bindings](api/bindings.md) — 190 functions, handle and value-struct classes, constants, the translations, the modules compiled in.

# Architecture

* [Lifetimes](architecture/lifetimes.md) — paint references, gradient hand-over and lending, canvas targets, savers, borrowed bytes, callbacks.
* [Safety checks](architecture/checks.md) — the inputs ThorVG trusts and the binding refuses, the mask-getter type error, symbol export.

# Runbooks

* [Build, install, test](runbooks/build.md) — Mac NTS/ZTS, Debian, the crash sweep, updating the vendored tag.
