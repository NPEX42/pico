#pragma once

#include "common.h"
#include "maths.h"

typedef struct PicoRenderer PicoRenderer;
typedef struct PicoImage PicoImage;
typedef struct Vertex2D {
    PVec2 position;
    PVec3 color;
    PVec2 uv;
} Vertex2D;

typedef struct PicoSprite {
    PVec2 position, size;
    PVec3 color;
    PicoImage* img;
} PicoSprite;

PicoRenderer* create_renderer(U16 max_triangles);

void pico_background(F32 r, F32 g, F32 b);
void pico_flush(PicoRenderer* r);
void pico_push_triangle(PicoRenderer* r, Vertex2D v[3]);

void pico_quad_centered(PicoRenderer* r, float x, float y, PVec3 color, float width, float height);
void pico_sprite_centered(PicoRenderer* r, float x, float y, PicoImage* img, float width, float height, PVec3 color);
void pico_sprite(PicoRenderer* r, PicoSprite* spr);

void pico_set_proj(PicoRenderer* r, PMatrix* proj);