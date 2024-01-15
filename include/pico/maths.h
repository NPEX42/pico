#pragma once
#include "common.h"
#include "math.h"

typedef struct PVec2 {
    F32 x, y;
} PVec2;

PVec2 pv2_add(PVec2 lhs, PVec2 rhs);
PVec2 pv2_sub(PVec2 lhs, PVec2 rhs);
F32   pv2_dot(PVec2 lhs, PVec2 rhs);
PVec2 pv2_div(PVec2 lhs, F32 divisor);
PVec2 pv2_scale(PVec2 lhs, F32 scale);
F32   pv2_mag_sq(PVec2 v);
F32   pv2_mag(PVec2 v);
