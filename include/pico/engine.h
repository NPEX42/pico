#pragma once

typedef struct PicoApp PicoApp;
typedef struct GLFWwindow GLFWwindow;

typedef struct PicoEngine {
    PicoApp* app;
    GLFWwindow* window;
} PicoEngine;