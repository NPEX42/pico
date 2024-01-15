#include <stdio.h>
#include "pico.h"

void onCreate();
bool onUpdate();
void onRender();
void onDestroy();

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
        .windowInfo = &info
    };
    pico_start(&app);

    return 0;
}


void onCreate() {


}

bool onUpdate() {

    return true;
}

void onRender() {


}

void onDestroy() {


}