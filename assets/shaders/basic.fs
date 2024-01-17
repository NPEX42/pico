#version 410
layout(location = 0) in vec3 iColor; 

layout(location = 0) out vec4 oPixel;

void main() {
    oPixel = vec4(iColor, 1);
}