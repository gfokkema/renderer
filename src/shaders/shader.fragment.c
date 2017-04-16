#version 450 core

layout(location=0) out vec3 frag_color;

     in vec2 frag_texcoord;
flat in uint frag_texid;

uniform sampler2D tex[16];

void main() {
    frag_color = texture(tex[frag_texid], frag_texcoord).rgb;
}
