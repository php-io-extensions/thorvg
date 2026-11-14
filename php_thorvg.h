#ifndef PHP_THORVG_H
#define PHP_THORVG_H

extern zend_module_entry thorvg_module_entry;
#define phpext_thorvg_ptr &thorvg_module_entry

#define PHP_THORVG_VERSION "0.11.0"

/* ThorVG tag v1.1.3. A newer library lands only by replacing lib/thorvg/ from a published tag. */
#define PHP_THORVG_UPSTREAM_COMMIT "589bc4120f2097fb1b135e552c2ef39f6581612b"

/* Modules compiled in (src/thorvg-config/config.h). */
#define PHP_THORVG_MODULES "cpu engine, svg, png, jpg, webp, ttf, otf, media, gif saver"

#if defined(ZTS) && defined(COMPILE_DL_THORVG)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
