#version 330 core

layout(location = 0) in vec3 vert_pos;
layout(location = 1) in vec2 vert_texcoord;

out vec2 frag_texcoord;

uniform mat4 mvp;

void main() {
    frag_texcoord = vert_texcoord;

    gl_Position = mvp * vec4(vert_pos, 1);
}
