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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 4.0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return img;
}

PicoImage* load_image(const cstr_t path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
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
    glBindTexture(GL_TEXTURE_2D, img->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void attach_image(PicoImage* img ,int unit) {
    glActiveTexture(GL_TEXTURE0 + unit); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, img->ID);
}