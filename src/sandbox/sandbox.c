#include <stdio.h>
#include "pico.h"

void onCreate(PicoEngine* pico);
bool onUpdate();
void onRender();
void onDestroy();

void onResize(int width, int height);

int main(void) {
    printf("Hello, World\n");
    if (!pico_init()) {
        fprintf(stderr, "Failed To Initialize Engine\n");
        return 1;
    }

    WindowInfo info = (WindowInfo) {
        .width = 1080,
        .height = 720,
        .title = "Sandbox"
    };

    PicoApp app = (PicoApp) {
        .onCreate = onCreate,
        .onUpdate = onUpdate,
        .onRender = onRender,
        .onDestroy = onDestroy,
        .onFramebufferResize = onResize,
        .windowInfo = &info
    };

    pico_start(&app);

    return 0;
}

PicoEngine* gPico = NULL;
PicoImage* gUV = NULL;
PicoImage* icon;

PicoSprite* sprites = NULL;

void onCreate(PicoEngine* pico) {
    gPico = pico;

    gUV = load_image("assets/textures/uv_grid1024.png");
    icon = load_image("assets/textures/DirIcon");
    pico_set_icon(pico, icon);

    printf("Texture Dims: %dx%d\n", gUV->width, gUV->height);

    sprites = malloc(sizeof(PicoSprite) * 10);

    for (int i = 0; i < 10; i++) {
        sprites[i].img = gUV;
        sprites[i].position = (PVec2) {(i * 1.5) / 10.0 - 0.67, 0};
        sprites[i].size = (PVec2) {0.5, 0.5};
        sprites[i].color = (PVec3) {1, 1, 1};
    }
}

bool onUpdate() {

    return true;
}

void onRender() {
    pico_background(0.1, 0.2, 0.3);
    for (int i = 0; i < 10; i++) {
        pico_sprite(gPico->renderer, &sprites[i]);
    }

    

}

void onDestroy() {


}

void onResize(int width, int height) {
    printf("Resize: (%d, %d)\n", width, height);
}