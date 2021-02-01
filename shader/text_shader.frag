#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 color;
uniform sampler2D tex;

void main() {
    FragColor = color*texture(tex, TexCoord); 

}
