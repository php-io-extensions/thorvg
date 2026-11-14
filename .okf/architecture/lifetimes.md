---
type: Architecture
title: Lifetimes
description: What the binding does with ThorVG's ownership rules so PHP never reaches freed memory.
resource: src/runtime.c
tags: [thorvg, memory]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
---

# Lifetimes

- **Paints**: one PHP object per pointer (registry in module globals), each holding one ThorVG reference (`tvg_paint_ref` on wrap, `tvg_paint_unref(free)` on free). `tvg_paint_unref` refuses to go below the references `tvg_paint_ref` took through that object (`user_refs`).
- **Gradients** have no refcount and ThorVG deletes them on replacement, solid colour, `tvg_shape_reset` or with their paint. Setting a free gradient releases its object. Borrowed gradients (`tvg_shape_get_gradient`/`_get_stroke_gradient`) hold a reference on their shape and are checked against its current fill and stroke fill on every use. Borrowed ones cannot be set elsewhere or deleted. Text gradients are never handed back (no getter).
- **Canvases** keep their target string in `keep`; `set_target` swaps it only on success (ThorVG refuses a new target mid-draw); free and `tvg_canvas_destroy` sync first.
- **Animations** hold a reference on their picture, so `Saver::save(Animation*)` (deletes the animation when the picture's count is ≤ 1) never deletes one PHP owns.
- **Savers** keep the animation being saved until sync/del (GIF saver renders on a worker); free and del sync first.
- **Borrowed bytes** (`copy = false` strings) live until post-deactivate; fonts loaded from them are unloaded then (ThorVG's font table outlives requests).
- **Callbacks**: resolver records live until post-deactivate; their callable and data zvals are released at RSHUTDOWN, before the object store is freed. The accessor's record is on the stack (synchronous).
