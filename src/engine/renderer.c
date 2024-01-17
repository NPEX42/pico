#include "pico/renderer.h"
#include "pico/utils.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_INFOLOG (1024)

typedef struct PicoRenderer {
    Vertex2D* vertices;
    U16* triangles;
    U16 triangleCapacity, triangleCount, vertexCount;
    U32 vao, vbo, ibo, shader;
} PicoRenderer;

U32 load_shader(const cstr_t vertexPath, const cstr_t fragmentPath);


PicoRenderer* create_renderer(U16 max_triangles) {
    PicoRenderer* r = malloc(sizeof(PicoRenderer));
    r->triangleCapacity = max_triangles;
    r->triangleCount = 0;
    r->vertices = malloc(r->triangleCapacity * 3 * sizeof(Vertex2D));
    memset(r->vertices, 0, sizeof(r->vertices));
    r->triangles = malloc(r->triangleCapacity * sizeof(U16));
    memset(r->triangles, 0, sizeof(r->triangles));
    r->vertexCount = 0;

    glGenVertexArrays(1, &r->vao);
    glGenBuffers(1, &r->vbo);
    glGenBuffers(1, &r->ibo);

    glBindVertexArray(r->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * 3 * max_triangles, NULL, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), offsetof(Vertex2D, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), offsetof(Vertex2D, color));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U16) * max_triangles * 3, NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    r->shader = load_shader(
        "assets/shaders/basic.vs",
        "assets/shaders/basic.fs"
    );


    return r;
}

void pico_background(F32 r, F32 g, F32 b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pico_push_vertex(PicoRenderer* r, Vertex2D v) {
    r->vertices[r->vertexCount++] = v;
}

void pico_push_triangle(PicoRenderer* r, Vertex2D v[3]) {
    if (r->triangleCount == r->triangleCapacity) {
        pico_flush(r);
    }

    for (int i = 0; i < 3; i++) {
        r->triangles[r->triangleCount + i] = r->triangleCount + i;
    }
    

    pico_push_vertex(r, v[0]);
    pico_push_vertex(r, v[1]);
    pico_push_vertex(r, v[2]);

    r->triangleCount += 3;
}

void pico_flush(PicoRenderer* r) {
    if (r->triangleCount == 0) {
        return;
    }
    glUseProgram(r->shader);
    glBindVertexArray(r->vao);

    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * r->triangleCount * 3, r->vertices, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U16) * r->triangleCount * 3, r->triangles, GL_STREAM_DRAW);
    
    glDrawElements(GL_TRIANGLES, r->triangleCount, GL_UNSIGNED_SHORT, NULL);

    glBindVertexArray(0);

    r->triangleCount = 0;
    r->vertexCount = 0;

    memset(r->triangles, 0, r->triangleCapacity * sizeof(U16));
    memset(r->vertices, 0, r->triangleCapacity * sizeof(Vertex2D) * 3);
}






U32 load_shader(const cstr_t vertexPath, const cstr_t fragmentPath) {
    U32 program = glCreateProgram();
    U32 vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    char* vs_src;
    char* fs_src;
    vs_src = pico_read_text(vertexPath);
    
    if (!vs_src) {

        printf("Failed To Load Shader '%s'\n", vertexPath);

        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }
    fs_src = pico_read_text(fragmentPath);

    
    

    if (!fs_src) {

        printf("Failed To Load Shader '%s'\n", fragmentPath);

        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }
    printf("FS: \n%s\n", fs_src);
    printf("VS: \n%s\n", vs_src);

    glShaderSource(vs, 1, &vs_src, NULL);
    glShaderSource(fs, 1, &fs_src, NULL);

    glCompileShader(vs);
    glCompileShader(fs);

    U32 status = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[MAX_INFOLOG];
        glGetShaderInfoLog(vs, MAX_INFOLOG, NULL, infoLog);
        printf("Vertex Shader Log:\n%s", infoLog);
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[MAX_INFOLOG];
        glGetShaderInfoLog(fs, MAX_INFOLOG, NULL, infoLog);
        printf("Fragment Shader Log:\n%s", infoLog);
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[MAX_INFOLOG];
        glGetProgramInfoLog(program, MAX_INFOLOG, NULL, infoLog);
        printf("Program Info Log:\n%s", infoLog);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}


void pico_quad_centered(PicoRenderer* r,  float x, float y, PVec3 color, float width, float height) {
    
    PVec2 BL = (PVec2) {
        x - width / 2,
        y - height / 2
    };

    PVec2 TL = (PVec2) {
        x - width / 2,
        y + height / 2
    };

    PVec2 BR = (PVec2) {
        x + width / 2,
        y - height / 2
    };

    PVec2 TR = (PVec2) {
        x + width / 2,
        y + height / 2
    };

    Vertex2D t1[3] = {
        {BL, color}, {BR, color}, {TL, color}  
    };

    Vertex2D t2[3] = {
        {TR, color}, {BR, color}, {TL, color} 
    };

    pico_push_triangle(r, t1);
    pico_push_triangle(r, t2);


}

