#version 330 core
//#extension GL_ARB_separate_shader_objects : enable

in vec3 position;

uniform mat4 mvp = mat4(1.0);

void main() {
    gl_Position = mvp * vec4(position, 1.0);
}

