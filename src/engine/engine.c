#include "pico.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
bool pico_init(void) {
    printf("Pico Engine v%d.%d\n", PICO_MAJOR, PICO_MINOR);
    return glfwInit();
}

void pico_start(PicoApp* app) {
    if (!app) {
        return;
    }

    WindowInfo* info = app->windowInfo;

    PicoEngine engine = {0};
    engine.app = app;
    engine.window = glfwCreateWindow(info->width, info->height, info->title, NULL, NULL);

    if (app->onCreate) {
        app->onCreate();
    }

    if (!app->onRender || !app->onUpdate) {
        return;
    }

    while (app->onUpdate() && !glfwWindowShouldClose(engine.window)) {
        glfwPollEvents();
        app->onRender();
        glfwSwapBuffers(engine.window);
    }

    if (app->onDestroy) {
        app->onDestroy();
    }
}