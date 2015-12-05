#include "context.h"

// An array of 3 vectors which represents 3 vertices
const std::vector<float> vertex_buffer_data({
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
});

Context::Context()
: vbo(GL_ARRAY_BUFFER)
{
}

Context::~Context()
{
}

void Context::create()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Belongs to some scene class or something like it.
    this->program.create();
    this->program.load("../src/shaders/shader.vertex.c", "../src/shaders/shader.fragment.c");
    this->vao.create();
    this->vao.bind();
    this->vbo.create();
    this->vbo.bind();
    this->vbo.load(vertex_buffer_data, GL_STATIC_DRAW);
}

void Context::destroy()
{
    this->program.destroy();
    this->vbo.destroy();
    this->vao.destroy();
}
