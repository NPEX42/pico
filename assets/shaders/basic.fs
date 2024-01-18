#version 410
layout(location = 0) in vec3 iColor; 
layout(location = 1) in vec2 iUV;

layout(location = 0) out vec4 oPixel;

uniform sampler2D uDiffuse;
void main() {
    oPixel = vec4(iColor, 1) * texture(uDiffuse, iUV);
}