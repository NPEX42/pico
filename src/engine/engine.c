#include "pico.h"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_QUADS 1024

void _resizeFramebufferHandler(GLFWwindow* window, int width, int height) {
    PicoApp* app = glfwGetWindowUserPointer(window);
    glViewport(0, 0, width, height);
    if (app->onFramebufferResize) {
        app->onFramebufferResize(width, height);
    }
}

bool pico_init(void) {
    printf("Pico Engine v%d.%d\n", PICO_MAJOR, PICO_MINOR);
    return glfwInit();
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    if (id == 0x20071) {  return; }

  fprintf( stdout, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, id=0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, id, message );
}
void pico_start(PicoApp* app) {
    if (!app) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    WindowInfo* info = app->windowInfo;

    PicoEngine engine = {0};
    engine.app = app;
    engine.window = glfwCreateWindow(info->width, info->height, info->title, NULL, NULL);
    glfwMakeContextCurrent(engine.window);

    glfwSetWindowUserPointer(engine.window, app);

    glfwSetFramebufferSizeCallback(engine.window, _resizeFramebufferHandler);

    gladLoadGLLoader((void*)glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback( MessageCallback, 0 );

    printf("GL: %s\n", glGetString(GL_VERSION));

    engine.renderer = create_renderer(2 * MAX_QUADS);

    if (app->onCreate) {
        app->onCreate(&engine);
    }

    if (!app->onRender || !app->onUpdate) {
        return;
    }

    while (app->onUpdate() && !glfwWindowShouldClose(engine.window)) {
        glfwPollEvents();
        app->onRender();
        pico_flush(engine.renderer);
        glfwSwapBuffers(engine.window);
    }

    if (app->onDestroy) {
        app->onDestroy();
    }
}


void pico_set_icon(PicoEngine* engine, PicoImage* icon) {
    GLFWimage img = (GLFWimage) {
        .width = icon->width,
        .height = icon->height,
        .pixels = icon->pixels
    };
    glfwSetWindowIcon(engine->window, 1, &img);
}