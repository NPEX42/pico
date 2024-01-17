#version 410
layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColor;

layout(location = 0) out vec3 fragColor;
void main() {
    gl_Position = vec4(vPosition, 0, 1);
    fragColor = vColor;
}