#pragma once
#include "common.h"
#include "math.h"

typedef struct PVec2 {
    F32 x, y;
} PVec2;

typedef struct PVec3 {
    F32 x, y, z;
} PVec3;

// M[]
typedef struct PMatrix {
    float values[4][4];
} PMatrix;

PVec2 pv2_add(PVec2 lhs, PVec2 rhs);
PVec2 pv2_sub(PVec2 lhs, PVec2 rhs);
F32   pv2_dot(PVec2 lhs, PVec2 rhs);
PVec2 pv2_div(PVec2 lhs, F32 divisor);
PVec2 pv2_scale(PVec2 lhs, F32 scale);
F32   pv2_mag_sq(PVec2 v);
F32   pv2_mag(PVec2 v);


PMatrix pm_mul(PMatrix a, PMatrix b);
PMatrix pm_ident(PMatrix m);
PMatrix pm_ortho(PMatrix m, float top, float bottom, float left, float right, float far, float near);
