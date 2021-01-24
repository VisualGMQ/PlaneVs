#version 330 core
layout (location = 0) in vec4 Pos;

void main() {
    gl_Position = vec4(Pos.xy, 0, 1);
}
