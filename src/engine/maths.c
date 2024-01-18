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



PMatrix pm_mul(PMatrix a, PMatrix b) {
    PMatrix c = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            c.values[i][j] = a.values[i][j] * a.values[j][i];
        }
    }
    return c;
}

PMatrix pm_ident(PMatrix m) {
    PMatrix c = {0};
        for (int j = 0; j < 4; j++) {
            c.values[j][j] = 1;
        }
    return c;
}

PMatrix pm_ortho(PMatrix m, float top, float bottom, float left, float right, float far, float near) {
    m.values[0][0] = 2 / (right - left);
    m.values[0][3] = - ((right + left) / (right - left));
    m.values[1][1] = 2 / (top - bottom);
    m.values[1][3] = - ((top + bottom) / (top - bottom));
    m.values[2][2] = (-2) / (far - near);
    m.values[2][3] = - ((far + near) / (far - near));
    m.values[3][3] = 1;
    return m;
}