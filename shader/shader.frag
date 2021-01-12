#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D tex;
uniform vec4 color;
uniform vec3 keycolor;

void main() {
    vec4 tex_color = texture(tex, TexCoord);
    if (tex_color.rgb == keycolor) {
        discard;
    }else {
        FragColor = color*texture(tex, TexCoord);
    }
}
