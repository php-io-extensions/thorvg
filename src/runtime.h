/*
 * The binding's shared machinery: handle objects and their lifetimes, the paint and
 * gradient registries, value structs, list readers, and the checks ThorVG does not make.
 * The rules are in docs/superpowers/specs/2026-11-13-thorvg-design.md, "Lifetimes".
 */

#ifndef TVG_RUNTIME_H
#define TVG_RUNTIME_H

#include "php.h"
#include "thorvg_capi.h"
#include <pthread.h>

/* Handle kinds, one class each. */
enum {
	TVG_K_CANVAS,
	TVG_K_PAINT,
	TVG_K_GRADIENT,
	TVG_K_SAVER,
	TVG_K_ANIMATION,
	TVG_K_ACCESSOR,
	TVG_K_VIDEO,
	TVG_K_COUNT
};

typedef struct {
	void *ptr;          /* NULL once released (*_del, tvg_canvas_destroy, a replaced gradient) */
	int kind;
	Tvg_Paint owner;    /* borrowed gradients: the shape that owns it (one reference held); NULL while PHP owns it */
	zend_long user_refs; /* paints: references taken by tvg_paint_ref() that tvg_paint_unref() may give back */
	Tvg_Paint picture;  /* animations: their picture, one reference held */
	zval keep;          /* canvases: the target string; savers: the animation being saved; else UNDEF */
	zend_object std;
} tvg_handle_obj;

static inline tvg_handle_obj *tvg_handle_from(zend_object *o) { return (tvg_handle_obj *) ((char *) o - XtOffsetOf(tvg_handle_obj, std)); }

extern zend_class_entry *tvg_handle_ce[TVG_K_COUNT];
extern zend_class_entry *tvg_point_ce, *tvg_matrix_ce, *tvg_region_ce, *tvg_color_stop_ce, *tvg_text_metrics_ce,
	*tvg_glyph_metrics_ce, *tvg_wgcontext_ce, *tvg_audio_info_ce;

ZEND_BEGIN_MODULE_GLOBALS(thorvg)
	HashTable paints;     /* Tvg_Paint -> zend_object*, one object per pointer */
	HashTable gradients;  /* Tvg_Gradient -> zend_object* */
	HashTable borrowed;   /* strings ThorVG reads without a copy, kept until post-deactivate */
	HashTable fonts;      /* font names loaded from borrowed bytes, unloaded at post-deactivate */
	HashTable callbacks;  /* tvg_callback records handed to ThorVG, freed at post-deactivate */
	bool live;
ZEND_END_MODULE_GLOBALS(thorvg)

ZEND_EXTERN_MODULE_GLOBALS(thorvg)
#define TVG_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(thorvg, v)

void tvg_runtime_minit(int module_number);
void tvg_runtime_rinit(void);
void tvg_runtime_rshutdown(void);
void tvg_runtime_post_deactivate(void);

/* The live pointer of a handle argument of `kind`, or NULL with ValueError thrown (released). */
void *tvg_handle_arg(zval *zv, int kind, uint32_t arg_num);
/* A new handle object of `kind` owning ptr (NULL: null). Paints and gradients go through their wrappers. */
void tvg_handle_new(int kind, void *ptr, zval *out);
/* Marks a handle released: later use throws. Does not touch the native object. */
void tvg_handle_release(zend_object *o);

/*
 * The paint argument, checked against `type` (TVG_TYPE_UNDEF: any). A wrong type throws TypeError
 * naming the function's expectation: ThorVG would cast it unchecked.
 */
Tvg_Paint tvg_paint_arg(zval *zv, Tvg_Type type, uint32_t arg_num);
/* The object for a paint pointer, one per pointer, holding one reference (NULL: null). */
void tvg_paint_wrap(Tvg_Paint paint, zval *out);

/*
 * The gradient argument. Released: ValueError. Borrowed (from tvg_shape_get_gradient or
 * tvg_shape_get_stroke_gradient): checked against its shape's current gradients, and released
 * with ValueError once the shape no longer holds it.
 */
Tvg_Gradient tvg_gradient_arg(zval *zv, uint32_t arg_num);
/* The object for a gradient pointer. `owner` NULL: PHP owns it; else the shape it is borrowed from. */
void tvg_gradient_wrap(Tvg_Gradient gradient, Tvg_Paint owner, zval *out);
/* A gradient a paint may take: one PHP owns (a borrowed one would be owned twice: ValueError, false). */
bool tvg_gradient_can_attach(zval *gradient_zv, uint32_t arg_num);
/* The paint now owns it: the object is released, since ThorVG may delete it at any later call. */
void tvg_gradient_attached(zval *gradient_zv);

/*
 * A PHP callable and its data, handed to ThorVG as a C callback's user data. Freed at
 * post-deactivate, after every object of the request, so ThorVG never holds a freed one.
 */
typedef struct {
	zval callable;
	zval data;
	pthread_t thread; /* the thread that registered it: the only one that may call PHP */
} tvg_callback;

tvg_callback *tvg_callback_new(zval *callable, zval *data);
/* Calls it with args (retval: IS_UNDEF on failure). False off its thread, or when the call failed or threw. */
bool tvg_callback_call(tvg_callback *cb, zval *args, uint32_t argc, zval *retval);

/* Keeps a string alive until post-deactivate (borrowed bytes). */
void tvg_borrow(zend_string *s);
/* Remembers a font name to unload at post-deactivate. */
void tvg_borrow_font(const char *name);

/*
 * Memory arguments: a string at least `need` bytes long (ValueError otherwise), or an address,
 * trusted. Sets *bytes; *str is the string or NULL.
 */
bool tvg_memory_arg(zend_string *str, zend_long address, size_t need, uint32_t arg_num, const void **bytes);

/* Value structs. read: object -> C; write: C -> existing object; new: C -> new object. */
void tvg_point_read(zend_object *o, Tvg_Point *out);
void tvg_point_write(zend_object *o, const Tvg_Point *in);
void tvg_point_new(const Tvg_Point *in, zval *out);
void tvg_matrix_read(zend_object *o, Tvg_Matrix *out);
void tvg_matrix_write(zend_object *o, const Tvg_Matrix *in);
void tvg_region_new(const Tvg_Region *in, zval *out);
bool tvg_color_stop_read(zend_object *o, Tvg_Color_Stop *out, uint32_t arg_num);
void tvg_color_stop_new(const Tvg_Color_Stop *in, zval *out);
void tvg_text_metrics_write(zend_object *o, const Tvg_Text_Metrics *in);
void tvg_glyph_metrics_write(zend_object *o, const Tvg_Glyph_Metrics *in);
void tvg_wgcontext_read(zend_object *o, Tvg_WgContext *out);

/* `count` elements of a list argument, after checking count <= its length (ValueError). emalloc'd; NULL when count is 0. */
bool tvg_list_count(HashTable *list, zend_long count, uint32_t arg_num);
Tvg_Point *tvg_points_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok);
Tvg_Path_Command *tvg_commands_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok);
float *tvg_floats_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok);
Tvg_Color_Stop *tvg_stops_read(HashTable *list, zend_long count, uint32_t arg_num, bool *ok);

/* A value within [min, max] (ValueError naming `what`). */
bool tvg_range(zend_long value, zend_long min, zend_long max, const char *what, uint32_t arg_num);
/* A uint8_t / uint32_t / int32_t argument. */
#define tvg_u8(v, n) tvg_range((v), 0, 255, "between 0 and 255", (n))
#define tvg_u32(v, n) tvg_range((v), 0, UINT32_MAX, "between 0 and 4294967295", (n))
#define tvg_i32(v, n) tvg_range((v), INT32_MIN, INT32_MAX, "a 32-bit signed integer", (n))

/*
 * Path coordinates: finite (ValueError naming the first bad argument). ThorVG's stroker never
 * finishes on some NaN or infinite geometry (a stroked circle of NaN radius, a NaN start point).
 */
bool tvg_finite_args(const double *values, int count, uint32_t first_arg);

/* A path ThorVG opens: open_basedir (false with a warning, as file functions do). */
bool tvg_path_allowed(const char *path);
/*
 * A path ThorVG tries every loader on: valid UTF-8 (ValueError). On macOS the media loader turns it
 * into an NSString, nil for invalid UTF-8, and NSURL then throws an exception that aborts PHP.
 */
bool tvg_path_utf8(const char *path, size_t len, uint32_t arg_num);

/* Assigns a by-reference argument; false when assigning threw. */
#define TVG_REF_LONG(zv, v) ZEND_TRY_ASSIGN_REF_LONG((zv), (zend_long) (v))
#define TVG_REF_DOUBLE(zv, v) ZEND_TRY_ASSIGN_REF_DOUBLE((zv), (double) (v))

#endif
