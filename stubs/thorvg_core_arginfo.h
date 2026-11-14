/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 2d2cf91068b191816ae515f21516fb1ddb5b7786 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_engine_version, 0, 4, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, major, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, minor, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, micro, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, version, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(tvg_engine_version);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_engine_version, arginfo_tvg_engine_version)
	ZEND_FE_END
};
