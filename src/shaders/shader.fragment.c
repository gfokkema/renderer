#version 330 core

in vec2 frag_texcoord;

layout(location=0) out vec3 frag_color;

uniform sampler2D tex;

void main() {
    frag_color = texture(tex, frag_texcoord).rgb;
}
