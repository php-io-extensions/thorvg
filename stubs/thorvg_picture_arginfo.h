/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f6e764bfd74e15f7f3425e48aca0f28513428068 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_picture_new, 0, 0, Tvg_Paint, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_load, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_load_raw, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_MASK(0, data, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, copy, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_load_alpha, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_load_data, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_MASK(0, data, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mimetype, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, rpath, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, copy, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_set_asset_resolver, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, resolver, IS_CALLABLE, 1)
	ZEND_ARG_TYPE_INFO(0, data, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_set_size, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_get_size, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, w, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, h, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_set_origin, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_get_origin, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(1, x, IS_DOUBLE, 1)
	ZEND_ARG_TYPE_INFO(1, y, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_picture_get_paint, 0, 2, Tvg_Paint, 1)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_set_filter, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, method, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_picture_set_accessible, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, picture, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, accessible, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_scene_new arginfo_tvg_picture_new

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_insert, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, target, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, at, Tvg_Paint, 1)
ZEND_END_ARG_INFO()

#define arginfo_tvg_scene_remove arginfo_tvg_scene_add

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_clear_effects, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_gaussian_blur, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, direction, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, border, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_motion_blur, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, distance, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_drop_shadow, 0, 9, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, distance, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sigma, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, quality, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_fill, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_tint, 0, 8, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, black_r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, black_g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, black_b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, white_r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, white_g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, white_b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, intensity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_scene_add_effect_tritone, 0, 11, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, scene, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, shadow_r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadow_g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadow_b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, midtone_r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, midtone_g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, midtone_b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, highlight_r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, highlight_g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, highlight_b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, blend, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_text_new arginfo_tvg_picture_new

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_font, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_size, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_text, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, utf8, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_align, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_layout, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_wrap_mode, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_line_count, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_spacing, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, letter, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, line, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_italic, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, shear, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_outline, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_color, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_set_gradient, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, gradient, Tvg_Gradient, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_get_text_metrics, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, metrics, Tvg_Text_Metrics, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_text_get_glyph_metrics, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, text, Tvg_Paint, 0)
	ZEND_ARG_TYPE_INFO(0, ch, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, metrics, Tvg_Glyph_Metrics, 0)
	ZEND_ARG_TYPE_INFO(1, next, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_font_load, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_font_load_data, 0, 5, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_MASK(0, data, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mimetype, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, copy, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_font_unload arginfo_tvg_font_load

ZEND_FUNCTION(tvg_picture_new);
ZEND_FUNCTION(tvg_picture_load);
ZEND_FUNCTION(tvg_picture_load_raw);
ZEND_FUNCTION(tvg_picture_load_alpha);
ZEND_FUNCTION(tvg_picture_load_data);
ZEND_FUNCTION(tvg_picture_set_asset_resolver);
ZEND_FUNCTION(tvg_picture_set_size);
ZEND_FUNCTION(tvg_picture_get_size);
ZEND_FUNCTION(tvg_picture_set_origin);
ZEND_FUNCTION(tvg_picture_get_origin);
ZEND_FUNCTION(tvg_picture_get_paint);
ZEND_FUNCTION(tvg_picture_set_filter);
ZEND_FUNCTION(tvg_picture_set_accessible);
ZEND_FUNCTION(tvg_scene_new);
ZEND_FUNCTION(tvg_scene_add);
ZEND_FUNCTION(tvg_scene_insert);
ZEND_FUNCTION(tvg_scene_remove);
ZEND_FUNCTION(tvg_scene_clear_effects);
ZEND_FUNCTION(tvg_scene_add_effect_gaussian_blur);
ZEND_FUNCTION(tvg_scene_add_effect_motion_blur);
ZEND_FUNCTION(tvg_scene_add_effect_drop_shadow);
ZEND_FUNCTION(tvg_scene_add_effect_fill);
ZEND_FUNCTION(tvg_scene_add_effect_tint);
ZEND_FUNCTION(tvg_scene_add_effect_tritone);
ZEND_FUNCTION(tvg_text_new);
ZEND_FUNCTION(tvg_text_set_font);
ZEND_FUNCTION(tvg_text_set_size);
ZEND_FUNCTION(tvg_text_set_text);
ZEND_FUNCTION(tvg_text_align);
ZEND_FUNCTION(tvg_text_layout);
ZEND_FUNCTION(tvg_text_wrap_mode);
ZEND_FUNCTION(tvg_text_line_count);
ZEND_FUNCTION(tvg_text_spacing);
ZEND_FUNCTION(tvg_text_set_italic);
ZEND_FUNCTION(tvg_text_set_outline);
ZEND_FUNCTION(tvg_text_set_color);
ZEND_FUNCTION(tvg_text_set_gradient);
ZEND_FUNCTION(tvg_text_get_text_metrics);
ZEND_FUNCTION(tvg_text_get_glyph_metrics);
ZEND_FUNCTION(tvg_font_load);
ZEND_FUNCTION(tvg_font_load_data);
ZEND_FUNCTION(tvg_font_unload);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_picture_new, arginfo_tvg_picture_new)
	ZEND_FE(tvg_picture_load, arginfo_tvg_picture_load)
	ZEND_FE(tvg_picture_load_raw, arginfo_tvg_picture_load_raw)
	ZEND_FE(tvg_picture_load_alpha, arginfo_tvg_picture_load_alpha)
	ZEND_FE(tvg_picture_load_data, arginfo_tvg_picture_load_data)
	ZEND_FE(tvg_picture_set_asset_resolver, arginfo_tvg_picture_set_asset_resolver)
	ZEND_FE(tvg_picture_set_size, arginfo_tvg_picture_set_size)
	ZEND_FE(tvg_picture_get_size, arginfo_tvg_picture_get_size)
	ZEND_FE(tvg_picture_set_origin, arginfo_tvg_picture_set_origin)
	ZEND_FE(tvg_picture_get_origin, arginfo_tvg_picture_get_origin)
	ZEND_FE(tvg_picture_get_paint, arginfo_tvg_picture_get_paint)
	ZEND_FE(tvg_picture_set_filter, arginfo_tvg_picture_set_filter)
	ZEND_FE(tvg_picture_set_accessible, arginfo_tvg_picture_set_accessible)
	ZEND_FE(tvg_scene_new, arginfo_tvg_scene_new)
	ZEND_FE(tvg_scene_add, arginfo_tvg_scene_add)
	ZEND_FE(tvg_scene_insert, arginfo_tvg_scene_insert)
	ZEND_FE(tvg_scene_remove, arginfo_tvg_scene_remove)
	ZEND_FE(tvg_scene_clear_effects, arginfo_tvg_scene_clear_effects)
	ZEND_FE(tvg_scene_add_effect_gaussian_blur, arginfo_tvg_scene_add_effect_gaussian_blur)
	ZEND_FE(tvg_scene_add_effect_motion_blur, arginfo_tvg_scene_add_effect_motion_blur)
	ZEND_FE(tvg_scene_add_effect_drop_shadow, arginfo_tvg_scene_add_effect_drop_shadow)
	ZEND_FE(tvg_scene_add_effect_fill, arginfo_tvg_scene_add_effect_fill)
	ZEND_FE(tvg_scene_add_effect_tint, arginfo_tvg_scene_add_effect_tint)
	ZEND_FE(tvg_scene_add_effect_tritone, arginfo_tvg_scene_add_effect_tritone)
	ZEND_FE(tvg_text_new, arginfo_tvg_text_new)
	ZEND_FE(tvg_text_set_font, arginfo_tvg_text_set_font)
	ZEND_FE(tvg_text_set_size, arginfo_tvg_text_set_size)
	ZEND_FE(tvg_text_set_text, arginfo_tvg_text_set_text)
	ZEND_FE(tvg_text_align, arginfo_tvg_text_align)
	ZEND_FE(tvg_text_layout, arginfo_tvg_text_layout)
	ZEND_FE(tvg_text_wrap_mode, arginfo_tvg_text_wrap_mode)
	ZEND_FE(tvg_text_line_count, arginfo_tvg_text_line_count)
	ZEND_FE(tvg_text_spacing, arginfo_tvg_text_spacing)
	ZEND_FE(tvg_text_set_italic, arginfo_tvg_text_set_italic)
	ZEND_FE(tvg_text_set_outline, arginfo_tvg_text_set_outline)
	ZEND_FE(tvg_text_set_color, arginfo_tvg_text_set_color)
	ZEND_FE(tvg_text_set_gradient, arginfo_tvg_text_set_gradient)
	ZEND_FE(tvg_text_get_text_metrics, arginfo_tvg_text_get_text_metrics)
	ZEND_FE(tvg_text_get_glyph_metrics, arginfo_tvg_text_get_glyph_metrics)
	ZEND_FE(tvg_font_load, arginfo_tvg_font_load)
	ZEND_FE(tvg_font_load_data, arginfo_tvg_font_load_data)
	ZEND_FE(tvg_font_unload, arginfo_tvg_font_unload)
	ZEND_FE_END
};
