#pragma once
#include "common.h"
typedef struct PicoImage {
    U16 width, height;
    U8* pixels;
    U32 ID;
} PicoImage;

PicoImage* new_image(U16 width, U16 height, U8* pixels);
PicoImage* load_image(const cstr_t path);

void pico_set_pixels(PicoImage* img, U8* pixels);