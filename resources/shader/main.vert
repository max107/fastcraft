#version 120

uniform vec4 mvp;

void main() {
    gl_Position = mvp;
}

