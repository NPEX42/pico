#pragma once

typedef struct PicoApp PicoApp;
typedef struct GLFWwindow GLFWwindow;
typedef struct PicoRenderer PicoRenderer;

typedef struct PicoEngine {
    PicoApp* app;
    GLFWwindow* window;
    PicoRenderer* renderer;
} PicoEngine;