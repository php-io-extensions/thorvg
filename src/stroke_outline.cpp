/*
 * Binding addition: the outline of a shape's stroke, from ThorVG's own CPU stroker.
 *
 * ThorVG's public API keeps a stroke as settings on a shape and computes its outline only while
 * drawing (cpu_engine/tvgSwShape.cpp, shapeGenStrokeRle). This runs the same three internal steps,
 * strokeReset(), strokeParseOutline() and strokeExportOutline(), and copies the outline out before
 * it is transformed, so its points are in the shape's own coordinates. Width, cap, join and miter
 * limit are the shape's; its dash pattern and trim are not applied (dash the path first).
 *
 * These are ThorVG internals, not its API: a ThorVG update may change them.
 */

#include "tvgCommon.h"
#include "tvgShape.h"
#include "tvgSwCommon.h"

using namespace tvg;

extern "C" int tvgphp_stroke_outline(const void *paint, uint8_t **cmds, uint32_t *cmd_cnt, float **xy, uint32_t *pt_cnt)
{
    *cmds = nullptr;
    *xy = nullptr;
    *cmd_cnt = 0;
    *pt_cnt = 0;

    auto shape = static_cast<const Paint*>(paint);
    if (!shape || shape->type() != Type::Shape) return (int) Result::InvalidArguments;
    auto& rs = to<ShapeImpl>(shape)->rs;
    if (!rs.stroke || rs.strokeWidth() <= 0.0f) return (int) Result::Success;
    if (rs.path.empty() || rs.path.cmds.empty() || rs.path.cmds.first() == PathCommand::CubicTo) return (int) Result::Success;

    SwMpool pool(0);
    auto source = pool.outline(0);
    source->path = &rs.path;
    source->fillRule = rs.rule;

    auto stroke = tvg::calloc<SwStroke>(1, sizeof(SwStroke));
    Matrix identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    strokeReset(stroke, &rs, identity, &pool, 0);
    if (!strokeParseOutline(stroke, *source)) {
        strokeFree(stroke);
        return (int) Result::Success;
    }
    auto out = strokeExportOutline(stroke, &pool, 0);
    auto& path = *out->path;

    *cmd_cnt = path.cmds.count;
    *pt_cnt = path.pts.count;
    *cmds = static_cast<uint8_t*>(std::malloc(path.cmds.count ? path.cmds.count : 1));
    *xy = static_cast<float*>(std::malloc(sizeof(float) * 2 * (path.pts.count ? path.pts.count : 1)));
    for (uint32_t i = 0; i < path.cmds.count; i++) (*cmds)[i] = (uint8_t) path.cmds[i];
    for (uint32_t i = 0; i < path.pts.count; i++) {
        (*xy)[2 * i] = path.pts[i].x;
        (*xy)[2 * i + 1] = path.pts[i].y;
    }

    strokeFree(stroke);
    return (int) Result::Success;
}
