#include "pico/image.h"
#include "stb/stb_image.h"
#include "glad/glad.h"

PicoImage* new_image(U16 width, U16 height, U8* pixels) {
    PicoImage* img = malloc(sizeof(PicoImage));
    img->width = width;
    img->height = height;
    img->pixels = malloc(4 * (width * height));
    if (pixels) {
        memcpy(img->pixels, pixels, 4 * (img->width * img->height));
    }

    glGenTextures(1, &img->ID);
    glBindTexture(GL_TEXTURE_2D, img->ID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    return img;
}

PicoImage* load_image(const cstr_t path) {
    int width, height, channels;
    U8* pixels = stbi_load(path, &width, &height, &channels, 4);
    if (pixels) {
        PicoImage* img = new_image(width, height, pixels);
        stbi_image_free(pixels);
        return img;
    } else {
        return NULL;
    }
}

void pico_set_pixels(PicoImage* img, U8* pixels) {
    memcpy(img->pixels, pixels, 4 * (img->width * img->height));
}