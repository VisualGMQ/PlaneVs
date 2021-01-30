#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;
uniform vec3 keycolor;

// if keycolor don't work at sometimes, please enlarg EPSILON
#define EPSILON 0.1

void main() {
    vec4 tex_color = texture(tex, TexCoord);
    if (abs(tex_color.r - keycolor.r) <= EPSILON &&
        abs(tex_color.g - keycolor.g) <= EPSILON &&
        abs(tex_color.b - keycolor.b) <= EPSILON) {
        discard;
    }else {
        FragColor = color*tex_color;
    }
}
