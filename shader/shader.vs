#version 330 core

layout (location = 0) in vec4 Pos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 transform;
out vec2 TexCoord;

void main() {
    TexCoord = Pos.zw;
    gl_Position = projection*model*transform*vec4(Pos.xy, 0, 1);
}
