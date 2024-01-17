#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct PicoEngine PicoEngine;

typedef void (*onCreateFn)(PicoEngine* pico);
typedef bool (*onUpdateFn)();
typedef void (*onRenderFn)();
typedef void (*onDestroyFn)();

typedef void (*onFramebufferResizeFn)(int width, int height);

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
    onFramebufferResizeFn onFramebufferResize;
    WindowInfo* windowInfo;
} PicoApp;