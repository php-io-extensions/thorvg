/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: c6e81d42448dc8145cdb37045d8d13138ae85a0a */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Canvas___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Tvg_Paint___construct arginfo_class_Tvg_Canvas___construct

#define arginfo_class_Tvg_Gradient___construct arginfo_class_Tvg_Canvas___construct

#define arginfo_class_Tvg_Saver___construct arginfo_class_Tvg_Canvas___construct

#define arginfo_class_Tvg_Animation___construct arginfo_class_Tvg_Canvas___construct

#define arginfo_class_Tvg_Accessor___construct arginfo_class_Tvg_Canvas___construct

#define arginfo_class_Tvg_Video___construct arginfo_class_Tvg_Canvas___construct

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Point___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 0, "0.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Matrix___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e11, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e12, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e13, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e21, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e22, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e23, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e31, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e32, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, e33, IS_DOUBLE, 0, "0.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Region___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, xMin, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, yMin, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, xMax, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, yMax, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Color_Stop___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offset, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, r, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, g, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, b, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, a, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Text_Metrics___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, ascent, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, descent, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, linegap, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, advance, IS_DOUBLE, 0, "0.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_Glyph_Metrics___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, advance, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, bearing, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, min, Tvg_Point, 1, "null")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, max, Tvg_Point, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Tvg_WgContext___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, instance, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, adapter, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, device, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

#define arginfo_class_Tvg_Audio_Info___construct arginfo_class_Tvg_Canvas___construct

ZEND_METHOD(Tvg_Canvas, __construct);
ZEND_METHOD(Tvg_Paint, __construct);
ZEND_METHOD(Tvg_Gradient, __construct);
ZEND_METHOD(Tvg_Saver, __construct);
ZEND_METHOD(Tvg_Animation, __construct);
ZEND_METHOD(Tvg_Accessor, __construct);
ZEND_METHOD(Tvg_Video, __construct);
ZEND_METHOD(Tvg_Point, __construct);
ZEND_METHOD(Tvg_Matrix, __construct);
ZEND_METHOD(Tvg_Region, __construct);
ZEND_METHOD(Tvg_Color_Stop, __construct);
ZEND_METHOD(Tvg_Text_Metrics, __construct);
ZEND_METHOD(Tvg_Glyph_Metrics, __construct);
ZEND_METHOD(Tvg_WgContext, __construct);
ZEND_METHOD(Tvg_Audio_Info, __construct);

static const zend_function_entry class_Tvg_Canvas_methods[] = {
	ZEND_ME(Tvg_Canvas, __construct, arginfo_class_Tvg_Canvas___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Paint_methods[] = {
	ZEND_ME(Tvg_Paint, __construct, arginfo_class_Tvg_Paint___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Gradient_methods[] = {
	ZEND_ME(Tvg_Gradient, __construct, arginfo_class_Tvg_Gradient___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Saver_methods[] = {
	ZEND_ME(Tvg_Saver, __construct, arginfo_class_Tvg_Saver___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Animation_methods[] = {
	ZEND_ME(Tvg_Animation, __construct, arginfo_class_Tvg_Animation___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Accessor_methods[] = {
	ZEND_ME(Tvg_Accessor, __construct, arginfo_class_Tvg_Accessor___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Video_methods[] = {
	ZEND_ME(Tvg_Video, __construct, arginfo_class_Tvg_Video___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Point_methods[] = {
	ZEND_ME(Tvg_Point, __construct, arginfo_class_Tvg_Point___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Matrix_methods[] = {
	ZEND_ME(Tvg_Matrix, __construct, arginfo_class_Tvg_Matrix___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Region_methods[] = {
	ZEND_ME(Tvg_Region, __construct, arginfo_class_Tvg_Region___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Color_Stop_methods[] = {
	ZEND_ME(Tvg_Color_Stop, __construct, arginfo_class_Tvg_Color_Stop___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Text_Metrics_methods[] = {
	ZEND_ME(Tvg_Text_Metrics, __construct, arginfo_class_Tvg_Text_Metrics___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Glyph_Metrics_methods[] = {
	ZEND_ME(Tvg_Glyph_Metrics, __construct, arginfo_class_Tvg_Glyph_Metrics___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_WgContext_methods[] = {
	ZEND_ME(Tvg_WgContext, __construct, arginfo_class_Tvg_WgContext___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_Tvg_Audio_Info_methods[] = {
	ZEND_ME(Tvg_Audio_Info, __construct, arginfo_class_Tvg_Audio_Info___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Tvg_Canvas(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Canvas", class_Tvg_Canvas_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Paint(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Paint", class_Tvg_Paint_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Gradient(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Gradient", class_Tvg_Gradient_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Saver(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Saver", class_Tvg_Saver_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Animation(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Animation", class_Tvg_Animation_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Accessor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Accessor", class_Tvg_Accessor_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Video(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Video", class_Tvg_Video_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Point(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Point", class_Tvg_Point_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_DOUBLE(&property_x_default_value, 0.0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_DOUBLE(&property_y_default_value, 0.0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_y_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Matrix(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Matrix", class_Tvg_Matrix_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_e11_default_value;
	ZVAL_DOUBLE(&property_e11_default_value, 0.0);
	zend_string *property_e11_name = zend_string_init("e11", sizeof("e11") - 1, 1);
	zend_declare_typed_property(class_entry, property_e11_name, &property_e11_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e11_name);

	zval property_e12_default_value;
	ZVAL_DOUBLE(&property_e12_default_value, 0.0);
	zend_string *property_e12_name = zend_string_init("e12", sizeof("e12") - 1, 1);
	zend_declare_typed_property(class_entry, property_e12_name, &property_e12_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e12_name);

	zval property_e13_default_value;
	ZVAL_DOUBLE(&property_e13_default_value, 0.0);
	zend_string *property_e13_name = zend_string_init("e13", sizeof("e13") - 1, 1);
	zend_declare_typed_property(class_entry, property_e13_name, &property_e13_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e13_name);

	zval property_e21_default_value;
	ZVAL_DOUBLE(&property_e21_default_value, 0.0);
	zend_string *property_e21_name = zend_string_init("e21", sizeof("e21") - 1, 1);
	zend_declare_typed_property(class_entry, property_e21_name, &property_e21_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e21_name);

	zval property_e22_default_value;
	ZVAL_DOUBLE(&property_e22_default_value, 0.0);
	zend_string *property_e22_name = zend_string_init("e22", sizeof("e22") - 1, 1);
	zend_declare_typed_property(class_entry, property_e22_name, &property_e22_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e22_name);

	zval property_e23_default_value;
	ZVAL_DOUBLE(&property_e23_default_value, 0.0);
	zend_string *property_e23_name = zend_string_init("e23", sizeof("e23") - 1, 1);
	zend_declare_typed_property(class_entry, property_e23_name, &property_e23_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e23_name);

	zval property_e31_default_value;
	ZVAL_DOUBLE(&property_e31_default_value, 0.0);
	zend_string *property_e31_name = zend_string_init("e31", sizeof("e31") - 1, 1);
	zend_declare_typed_property(class_entry, property_e31_name, &property_e31_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e31_name);

	zval property_e32_default_value;
	ZVAL_DOUBLE(&property_e32_default_value, 0.0);
	zend_string *property_e32_name = zend_string_init("e32", sizeof("e32") - 1, 1);
	zend_declare_typed_property(class_entry, property_e32_name, &property_e32_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e32_name);

	zval property_e33_default_value;
	ZVAL_DOUBLE(&property_e33_default_value, 0.0);
	zend_string *property_e33_name = zend_string_init("e33", sizeof("e33") - 1, 1);
	zend_declare_typed_property(class_entry, property_e33_name, &property_e33_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_e33_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Region(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Region", class_Tvg_Region_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_xMin_default_value;
	ZVAL_LONG(&property_xMin_default_value, 0);
	zend_string *property_xMin_name = zend_string_init("xMin", sizeof("xMin") - 1, 1);
	zend_declare_typed_property(class_entry, property_xMin_name, &property_xMin_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_xMin_name);

	zval property_yMin_default_value;
	ZVAL_LONG(&property_yMin_default_value, 0);
	zend_string *property_yMin_name = zend_string_init("yMin", sizeof("yMin") - 1, 1);
	zend_declare_typed_property(class_entry, property_yMin_name, &property_yMin_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_yMin_name);

	zval property_xMax_default_value;
	ZVAL_LONG(&property_xMax_default_value, 0);
	zend_string *property_xMax_name = zend_string_init("xMax", sizeof("xMax") - 1, 1);
	zend_declare_typed_property(class_entry, property_xMax_name, &property_xMax_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_xMax_name);

	zval property_yMax_default_value;
	ZVAL_LONG(&property_yMax_default_value, 0);
	zend_string *property_yMax_name = zend_string_init("yMax", sizeof("yMax") - 1, 1);
	zend_declare_typed_property(class_entry, property_yMax_name, &property_yMax_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_yMax_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Color_Stop(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Color_Stop", class_Tvg_Color_Stop_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_offset_default_value;
	ZVAL_DOUBLE(&property_offset_default_value, 0.0);
	zend_string *property_offset_name = zend_string_init("offset", sizeof("offset") - 1, 1);
	zend_declare_typed_property(class_entry, property_offset_name, &property_offset_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_offset_name);

	zval property_r_default_value;
	ZVAL_LONG(&property_r_default_value, 0);
	zend_string *property_r_name = zend_string_init("r", sizeof("r") - 1, 1);
	zend_declare_typed_property(class_entry, property_r_name, &property_r_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_r_name);

	zval property_g_default_value;
	ZVAL_LONG(&property_g_default_value, 0);
	zend_string *property_g_name = zend_string_init("g", sizeof("g") - 1, 1);
	zend_declare_typed_property(class_entry, property_g_name, &property_g_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_g_name);

	zval property_b_default_value;
	ZVAL_LONG(&property_b_default_value, 0);
	zend_string *property_b_name = zend_string_init("b", sizeof("b") - 1, 1);
	zend_declare_typed_property(class_entry, property_b_name, &property_b_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_b_name);

	zval property_a_default_value;
	ZVAL_LONG(&property_a_default_value, 0);
	zend_string *property_a_name = zend_string_init("a", sizeof("a") - 1, 1);
	zend_declare_typed_property(class_entry, property_a_name, &property_a_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_a_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Text_Metrics(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Text_Metrics", class_Tvg_Text_Metrics_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_ascent_default_value;
	ZVAL_DOUBLE(&property_ascent_default_value, 0.0);
	zend_string *property_ascent_name = zend_string_init("ascent", sizeof("ascent") - 1, 1);
	zend_declare_typed_property(class_entry, property_ascent_name, &property_ascent_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_ascent_name);

	zval property_descent_default_value;
	ZVAL_DOUBLE(&property_descent_default_value, 0.0);
	zend_string *property_descent_name = zend_string_init("descent", sizeof("descent") - 1, 1);
	zend_declare_typed_property(class_entry, property_descent_name, &property_descent_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_descent_name);

	zval property_linegap_default_value;
	ZVAL_DOUBLE(&property_linegap_default_value, 0.0);
	zend_string *property_linegap_name = zend_string_init("linegap", sizeof("linegap") - 1, 1);
	zend_declare_typed_property(class_entry, property_linegap_name, &property_linegap_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_linegap_name);

	zval property_advance_default_value;
	ZVAL_DOUBLE(&property_advance_default_value, 0.0);
	zend_string *property_advance_name = zend_string_init("advance", sizeof("advance") - 1, 1);
	zend_declare_typed_property(class_entry, property_advance_name, &property_advance_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_advance_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Glyph_Metrics(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Glyph_Metrics", class_Tvg_Glyph_Metrics_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_advance_default_value;
	ZVAL_DOUBLE(&property_advance_default_value, 0.0);
	zend_string *property_advance_name = zend_string_init("advance", sizeof("advance") - 1, 1);
	zend_declare_typed_property(class_entry, property_advance_name, &property_advance_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_advance_name);

	zval property_bearing_default_value;
	ZVAL_DOUBLE(&property_bearing_default_value, 0.0);
	zend_string *property_bearing_name = zend_string_init("bearing", sizeof("bearing") - 1, 1);
	zend_declare_typed_property(class_entry, property_bearing_name, &property_bearing_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_bearing_name);

	zval property_min_default_value;
	ZVAL_UNDEF(&property_min_default_value);
	zend_string *property_min_name = zend_string_init("min", sizeof("min") - 1, 1);
	zend_string *property_min_class_Tvg_Point = zend_string_init("Tvg_Point", sizeof("Tvg_Point")-1, 1);
	zend_declare_typed_property(class_entry, property_min_name, &property_min_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_min_class_Tvg_Point, 0, 0));
	zend_string_release(property_min_name);

	zval property_max_default_value;
	ZVAL_UNDEF(&property_max_default_value);
	zend_string *property_max_name = zend_string_init("max", sizeof("max") - 1, 1);
	zend_string *property_max_class_Tvg_Point = zend_string_init("Tvg_Point", sizeof("Tvg_Point")-1, 1);
	zend_declare_typed_property(class_entry, property_max_name, &property_max_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_max_class_Tvg_Point, 0, 0));
	zend_string_release(property_max_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_WgContext(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_WgContext", class_Tvg_WgContext_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_instance_default_value;
	ZVAL_LONG(&property_instance_default_value, 0);
	zend_string *property_instance_name = zend_string_init("instance", sizeof("instance") - 1, 1);
	zend_declare_typed_property(class_entry, property_instance_name, &property_instance_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_instance_name);

	zval property_adapter_default_value;
	ZVAL_LONG(&property_adapter_default_value, 0);
	zend_string *property_adapter_name = zend_string_init("adapter", sizeof("adapter") - 1, 1);
	zend_declare_typed_property(class_entry, property_adapter_name, &property_adapter_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_adapter_name);

	zval property_device_default_value;
	ZVAL_LONG(&property_device_default_value, 0);
	zend_string *property_device_name = zend_string_init("device", sizeof("device") - 1, 1);
	zend_declare_typed_property(class_entry, property_device_name, &property_device_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_device_name);

	return class_entry;
}

static zend_class_entry *register_class_Tvg_Audio_Info(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Tvg_Audio_Info", class_Tvg_Audio_Info_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_src_default_value;
	ZVAL_NULL(&property_src_default_value);
	zend_string *property_src_name = zend_string_init("src", sizeof("src") - 1, 1);
	zend_declare_typed_property(class_entry, property_src_name, &property_src_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_src_name);

	zval property_mimeType_default_value;
	ZVAL_NULL(&property_mimeType_default_value);
	zend_string *property_mimeType_name = zend_string_init("mimeType", sizeof("mimeType") - 1, 1);
	zend_declare_typed_property(class_entry, property_mimeType_name, &property_mimeType_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_mimeType_name);

	zval property_size_default_value;
	ZVAL_LONG(&property_size_default_value, 0);
	zend_string *property_size_name = zend_string_init("size", sizeof("size") - 1, 1);
	zend_declare_typed_property(class_entry, property_size_name, &property_size_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_size_name);

	zval property_offset_default_value;
	ZVAL_DOUBLE(&property_offset_default_value, 0.0);
	zend_string *property_offset_name = zend_string_init("offset", sizeof("offset") - 1, 1);
	zend_declare_typed_property(class_entry, property_offset_name, &property_offset_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_offset_name);

	zval property_volume_default_value;
	ZVAL_DOUBLE(&property_volume_default_value, 0.0);
	zend_string *property_volume_name = zend_string_init("volume", sizeof("volume") - 1, 1);
	zend_declare_typed_property(class_entry, property_volume_name, &property_volume_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_volume_name);

	zval property_active_default_value;
	ZVAL_FALSE(&property_active_default_value);
	zend_string *property_active_name = zend_string_init("active", sizeof("active") - 1, 1);
	zend_declare_typed_property(class_entry, property_active_name, &property_active_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_active_name);

	zval property_embedded_default_value;
	ZVAL_FALSE(&property_embedded_default_value);
	zend_string *property_embedded_name = zend_string_init("embedded", sizeof("embedded") - 1, 1);
	zend_declare_typed_property(class_entry, property_embedded_name, &property_embedded_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_embedded_name);

	return class_entry;
}
