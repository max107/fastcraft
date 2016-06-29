#version 120
#extension GL_ARB_geometry_shader4 : enable

uniform vec4 mvp;
uniform vec3 position;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
}

