/*
 * thorvg: 1:1 bindings of ThorVG 1.1.3's C API. The library is compiled into this
 * extension. Function, struct and constant names stay the C names.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_thorvg.h"

#include "ext/standard/info.h"

#include "thorvg_capi.h"
#include "runtime.h"
#include "../stubs/thorvg_core_arginfo.h"
#include "../stubs/thorvg_constants_arginfo.h"

void tvg_canvas_minit(void);
void tvg_paint_minit(void);
void tvg_shape_minit(void);
void tvg_gradient_minit(void);
void tvg_picture_minit(void);
void tvg_misc_minit(void);

ZEND_FUNCTION(tvg_engine_version)
{
	zval *major_zv, *minor_zv, *micro_zv, *version_zv;
	uint32_t major = 0, minor = 0, micro = 0;
	const char *version = NULL;
	Tvg_Result result;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ZVAL(major_zv)
		Z_PARAM_ZVAL(minor_zv)
		Z_PARAM_ZVAL(micro_zv)
		Z_PARAM_ZVAL(version_zv)
	ZEND_PARSE_PARAMETERS_END();

	result = tvg_engine_version(&major, &minor, &micro, &version);
	ZEND_TRY_ASSIGN_REF_LONG(major_zv, (zend_long) major);
	ZEND_TRY_ASSIGN_REF_LONG(minor_zv, (zend_long) minor);
	ZEND_TRY_ASSIGN_REF_LONG(micro_zv, (zend_long) micro);
	if (version != NULL) {
		ZEND_TRY_ASSIGN_REF_STRING(version_zv, version);
	} else {
		ZEND_TRY_ASSIGN_REF_NULL(version_zv);
	}
	if (EG(exception)) {
		RETURN_THROWS();
	}
	RETURN_LONG((zend_long) result);
}

static PHP_MINIT_FUNCTION(thorvg)
{
#if defined(ZTS) && defined(COMPILE_DL_THORVG)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	register_thorvg_constants_symbols(module_number);
	tvg_runtime_minit(module_number);
	tvg_canvas_minit();
	tvg_paint_minit();
	tvg_shape_minit();
	tvg_gradient_minit();
	tvg_picture_minit();
	tvg_misc_minit();
	return SUCCESS;
}

static PHP_RINIT_FUNCTION(thorvg)
{
#if defined(ZTS) && defined(COMPILE_DL_THORVG)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	tvg_runtime_rinit();
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(thorvg)
{
	tvg_runtime_rshutdown();
	return SUCCESS;
}

static ZEND_MODULE_POST_ZEND_DEACTIVATE_D(thorvg)
{
	tvg_runtime_post_deactivate();
	return SUCCESS;
}

static PHP_GINIT_FUNCTION(thorvg)
{
#if defined(COMPILE_DL_THORVG) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	memset(thorvg_globals, 0, sizeof(*thorvg_globals));
}

static PHP_MINFO_FUNCTION(thorvg)
{
	const char *version = NULL;

	tvg_engine_version(NULL, NULL, NULL, &version);
	php_info_print_table_start();
	php_info_print_table_header(2, "thorvg support", "enabled");
	php_info_print_table_row(2, "Version", PHP_THORVG_VERSION);
	php_info_print_table_row(2, "ThorVG version", version != NULL ? version : "unknown");
	php_info_print_table_row(2, "ThorVG commit", PHP_THORVG_UPSTREAM_COMMIT);
	php_info_print_table_row(2, "ThorVG modules", PHP_THORVG_MODULES);
	php_info_print_table_end();
}

zend_module_entry thorvg_module_entry = {
	STANDARD_MODULE_HEADER,
	"thorvg",
	ext_functions,
	PHP_MINIT(thorvg),
	NULL,
	PHP_RINIT(thorvg),
	PHP_RSHUTDOWN(thorvg),
	PHP_MINFO(thorvg),
	PHP_THORVG_VERSION,
	PHP_MODULE_GLOBALS(thorvg),
	PHP_GINIT(thorvg),
	NULL,
	ZEND_MODULE_POST_ZEND_DEACTIVATE_N(thorvg),
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_THORVG
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(thorvg)
#endif
