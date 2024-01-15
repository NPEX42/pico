#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef void (*onCreateFn)();
typedef bool (*onUpdateFn)();
typedef void (*onRenderFn)();
typedef void (*onDestroyFn)();

typedef struct WindowInfo {
    int width, height;
    const char* title;
    bool is_fullscreen;
} WindowInfo;

typedef struct PicoApp {
    onCreateFn onCreate;
    onDestroyFn onDestroy;
    onUpdateFn onUpdate;
    onRenderFn onRender;

    WindowInfo* windowInfo;
} PicoApp;