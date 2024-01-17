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

void onCreate(PicoEngine* pico) {
    gPico = pico;
}

bool onUpdate() {

    return true;
}

void onRender() {
    pico_background(0.1, 0.2, 0.3);
    pico_quad_centered(gPico->renderer,
        -0.5, 0.5, (PVec3) {1, 0, 0}, 0.5, 0.5
    );

    pico_quad_centered(gPico->renderer,
        0, 0, (PVec3) {0, 1, 0}, 0.5, 0.5
    );

    pico_quad_centered(gPico->renderer,
        0.5, -0.5, (PVec3) {0, 0, 1}, 0.5, 0.5
    );

}

void onDestroy() {


}

void onResize(int width, int height) {
    printf("Resize: (%d, %d)\n", width, height);
}