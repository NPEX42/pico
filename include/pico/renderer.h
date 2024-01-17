#pragma once

#include "common.h"
#include "maths.h"

typedef struct PicoRenderer PicoRenderer;
typedef struct Vertex2D {
    PVec2 position;
    PVec3 color;
} Vertex2D;

PicoRenderer* create_renderer(U16 max_triangles);

void pico_background(F32 r, F32 g, F32 b);
void pico_flush(PicoRenderer* r);
void pico_push_triangle(PicoRenderer* r, Vertex2D v[3]);

void pico_quad_centered(PicoRenderer* r, float x, float y, PVec3 color, float width, float height);