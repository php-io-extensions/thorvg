/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 86366d0f9c4ec8defe8e20021c9f0e2b9d01485f */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_engine_init, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threads, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_engine_term, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tvg_swcanvas_create, 0, 1, Tvg_Canvas, 1)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_swcanvas_set_target, 0, 6, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_MASK(0, buffer, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_swcanvas_get_alpha, 0, 5, IS_STRING, 0)
	ZEND_ARG_TYPE_MASK(0, buffer, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_swcanvas_get_target_address, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_glcanvas_create arginfo_tvg_swcanvas_create

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_glcanvas_set_target, 0, 8, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_INFO(0, display, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, surface, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_wgcanvas_create arginfo_tvg_swcanvas_create

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_wgcanvas_set_target, 0, 8, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instance, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_wgcanvas_set_target_with_context, 0, 7, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_OBJ_INFO(0, context, Tvg_WgContext, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cs, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_canvas_destroy arginfo_tvg_swcanvas_get_target_address

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_canvas_add, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_OBJ_INFO(0, paint, Tvg_Paint, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_canvas_insert, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_OBJ_INFO(0, target, Tvg_Paint, 0)
	ZEND_ARG_OBJ_INFO(0, at, Tvg_Paint, 1)
ZEND_END_ARG_INFO()

#define arginfo_tvg_canvas_remove arginfo_tvg_canvas_add

#define arginfo_tvg_canvas_update arginfo_tvg_swcanvas_get_target_address

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_canvas_draw, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_INFO(0, clear, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_tvg_canvas_sync arginfo_tvg_swcanvas_get_target_address

#define arginfo_tvg_canvas_get_dirty_regions_cnt arginfo_tvg_swcanvas_get_target_address

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_canvas_get_dirty_regions, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_INFO(1, regions, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(0, cnt, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tvg_canvas_set_viewport, 0, 5, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, canvas, Tvg_Canvas, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(tvg_engine_init);
ZEND_FUNCTION(tvg_engine_term);
ZEND_FUNCTION(tvg_swcanvas_create);
ZEND_FUNCTION(tvg_swcanvas_set_target);
ZEND_FUNCTION(tvg_swcanvas_get_alpha);
ZEND_FUNCTION(tvg_swcanvas_get_target_address);
ZEND_FUNCTION(tvg_glcanvas_create);
ZEND_FUNCTION(tvg_glcanvas_set_target);
ZEND_FUNCTION(tvg_wgcanvas_create);
ZEND_FUNCTION(tvg_wgcanvas_set_target);
ZEND_FUNCTION(tvg_wgcanvas_set_target_with_context);
ZEND_FUNCTION(tvg_canvas_destroy);
ZEND_FUNCTION(tvg_canvas_add);
ZEND_FUNCTION(tvg_canvas_insert);
ZEND_FUNCTION(tvg_canvas_remove);
ZEND_FUNCTION(tvg_canvas_update);
ZEND_FUNCTION(tvg_canvas_draw);
ZEND_FUNCTION(tvg_canvas_sync);
ZEND_FUNCTION(tvg_canvas_get_dirty_regions_cnt);
ZEND_FUNCTION(tvg_canvas_get_dirty_regions);
ZEND_FUNCTION(tvg_canvas_set_viewport);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(tvg_engine_init, arginfo_tvg_engine_init)
	ZEND_FE(tvg_engine_term, arginfo_tvg_engine_term)
	ZEND_FE(tvg_swcanvas_create, arginfo_tvg_swcanvas_create)
	ZEND_FE(tvg_swcanvas_set_target, arginfo_tvg_swcanvas_set_target)
	ZEND_FE(tvg_swcanvas_get_alpha, arginfo_tvg_swcanvas_get_alpha)
	ZEND_FE(tvg_swcanvas_get_target_address, arginfo_tvg_swcanvas_get_target_address)
	ZEND_FE(tvg_glcanvas_create, arginfo_tvg_glcanvas_create)
	ZEND_FE(tvg_glcanvas_set_target, arginfo_tvg_glcanvas_set_target)
	ZEND_FE(tvg_wgcanvas_create, arginfo_tvg_wgcanvas_create)
	ZEND_FE(tvg_wgcanvas_set_target, arginfo_tvg_wgcanvas_set_target)
	ZEND_FE(tvg_wgcanvas_set_target_with_context, arginfo_tvg_wgcanvas_set_target_with_context)
	ZEND_FE(tvg_canvas_destroy, arginfo_tvg_canvas_destroy)
	ZEND_FE(tvg_canvas_add, arginfo_tvg_canvas_add)
	ZEND_FE(tvg_canvas_insert, arginfo_tvg_canvas_insert)
	ZEND_FE(tvg_canvas_remove, arginfo_tvg_canvas_remove)
	ZEND_FE(tvg_canvas_update, arginfo_tvg_canvas_update)
	ZEND_FE(tvg_canvas_draw, arginfo_tvg_canvas_draw)
	ZEND_FE(tvg_canvas_sync, arginfo_tvg_canvas_sync)
	ZEND_FE(tvg_canvas_get_dirty_regions_cnt, arginfo_tvg_canvas_get_dirty_regions_cnt)
	ZEND_FE(tvg_canvas_get_dirty_regions, arginfo_tvg_canvas_get_dirty_regions)
	ZEND_FE(tvg_canvas_set_viewport, arginfo_tvg_canvas_set_viewport)
	ZEND_FE_END
};
