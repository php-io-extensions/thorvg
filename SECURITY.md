# Security Policy

## Supported versions

ext-thorvg is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in the
next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/thorvg](https://github.com/php-io-extensions/thorvg) repository's **Security** tab.
If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform and CPU, PHP build (NTS or ZTS), and
steps to reproduce (`php --ri thorvg` shows the extension version, the ThorVG commit it carries and
its modules).

A defect in ThorVG itself belongs with that project. Report it here as well when ext-thorvg should
guard against it.

## Security model

ThorVG trusts its caller with types, memory and lifetimes. ext-thorvg stands between PHP and ThorVG:

- **Images, SVG and fonts are trusted input.** ThorVG's own decoders (SVG, PNG through lodepng, JPG,
  WebP, TTF/OTF) parse what they are given. Load only files and data you trust. The SVG loader also
  opens files an SVG names (`<image href>`), relative to `rpath` or absolute, without asking PHP:
  `open_basedir` covers the paths the binding is handed, not the ones inside a document.
- **Types.** ThorVG casts a `Tvg_Paint` to the type each function expects without checking. The
  binding checks the paint's type first (`TypeError`), including a clip that is not a shape.
- **Lifetimes.** Paints are reference-counted and each `Tvg_Paint` object holds one reference, so
  ThorVG never frees a paint PHP can reach; `tvg_paint_unref` cannot give back that reference.
  Gradients are handed over to the shape they are set on, and gradients lent back by a shape are
  checked against it on every use. Canvases keep their target buffer and finish a draw before they
  go; savers keep the animation they render until it is done. A released handle refuses use.
- **Memory.** A canvas draws into its target string in place (an interned string is refused: it
  would be shared by every use of the literal). Strings ThorVG reads without copying stay alive
  until the request ends. `string|int` memory arguments also take an address, which the caller
  vouches for, as do the GL and WebGPU handles and `tvg_paint_set_data`.
- **Inputs ThorVG would trust.** Enum values outside their enum, channels outside 0..255, buffers
  shorter than their size, counts longer than their lists, negative or NaN dash lengths, a mask
  or clip on the paint itself, NaN or infinite path coordinates (ThorVG's stroker never finishes on
  some), and file paths that are not valid UTF-8 (on macOS ThorVG's media loader aborts the process on
  them) are each refused before ThorVG runs. `tools/sweep.php` calls every
  function with zero, negative, huge, infinite and NaN arguments in separate processes to keep it
  that way.
- **An upstream type error.** `tvg_paint_get_mask_method` declares its `target` as a paint but
  writes through it; the binding passes its own out-variable, so no paint is overwritten.
- **Files.** Every filename and resource directory the binding is handed goes through
  `open_basedir`.
- **Symbols.** The module exports `get_module` only, so another ThorVG in the process never takes
  over the binding's calls.
- **Callbacks.** The accessor callback runs on the calling thread, synchronously; an exception stops
  the walk. The asset and audio resolvers are only called by the Lottie loader, which this build
  does not have; a resolver called off the thread that set it answers false without running PHP.
- **Threads.** ThorVG renders on its own worker threads (`tvg_engine_init`), which never call PHP.
  Read a canvas's target only after `tvg_canvas_sync`.
