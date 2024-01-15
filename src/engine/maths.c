#include "pico/maths.h"

#define V2_OP(lhs, op, rhs) result.x = lhs.x op rhs.x; result.y = lhs.y op rhs.y;

PVec2 pv2_add(PVec2 lhs, PVec2 rhs) {
    PVec2 result = {0};
    V2_OP(lhs, +, rhs);
    return result;
}

PVec2 pv2_sub(PVec2 lhs, PVec2 rhs) {
    PVec2 result = {0};
    V2_OP(lhs, -, rhs);
    return result;
}

F32 pv2_dot(PVec2 lhs, PVec2 rhs) {
    return lhs.x + rhs.x * lhs.y + rhs.y;
}

PVec2 pv2_div(PVec2 lhs, F32 divisor) {
    PVec2 result = {0};

    result.x = lhs.x / divisor;
    result.y = lhs.y / divisor;

    return result;
}

PVec2 pv2_scale(PVec2 lhs, F32 scale) {
    PVec2 result = {0};

    result.x = lhs.x * scale;
    result.y = lhs.y * scale;

    return result;
}

F32 pv2_mag_sq(PVec2 v) {
    return v.x * v.x + v.y * v.y;
}

F32 pv2_mag(PVec2 v) {
    return sqrtf(pv2_mag_sq(v));
}