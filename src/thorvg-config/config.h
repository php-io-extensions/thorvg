/*
 * ThorVG 1.1.3's build configuration, as its meson.build would write config.h for this
 * extension's choice of modules. Only ThorVG's own sources see this file: they compile
 * with this directory first on the include path and without PHP's (whose config.h has the
 * same name).
 *
 * In: the CPU engine with partial rendering and the task scheduler; the SVG, PNG, JPG,
 * WebP, TTF/OTF and media loaders, ThorVG's own decoders (meson's 'static'); the GIF
 * saver; the C API; file IO. Out: the GL and WebGPU engines, the Lottie loader and its
 * expressions, OpenMP, logging. NEON or AVX2 is set by config.m4 per target.
 */

#ifndef PHP_THORVG_CONFIG_H
#define PHP_THORVG_CONFIG_H

#define THORVG_VERSION_STRING "1.1.3"

#define THORVG_CPU_ENGINE_SUPPORT 1
#define THORVG_PARTIAL_RENDER_SUPPORT 1
#define THORVG_THREAD_SUPPORT 1

#define THORVG_SVG_LOADER_SUPPORT 1
#define THORVG_PNG_LOADER_SUPPORT 1
#define THORVG_JPG_LOADER_SUPPORT 1
#define THORVG_WEBP_LOADER_SUPPORT 1
#define THORVG_SFNT_LOADER_SUPPORT 1
#define THORVG_TTF_LOADER_SUPPORT 1
#define THORVG_OTF_LOADER_SUPPORT 1
#define THORVG_MEDIA_LOADER_SUPPORT 1

#define THORVG_GIF_SAVER_SUPPORT 1

#define THORVG_CAPI_BINDING_SUPPORT 1
#define THORVG_FILE_IO_SUPPORT 1

#endif
