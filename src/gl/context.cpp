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
    this->destroy();
}

Status Context::create()
{
    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != STATUS_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return STATUS_ERR;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Shader vertexshader(GL_VERTEX_SHADER);
    Shader fragmentshader(GL_FRAGMENT_SHADER);
    if (vertexshader.load("../src/shaders/shader.vertex.c")) return STATUS_ERR;
    if (fragmentshader.load("../src/shaders/shader.fragment.c")) return STATUS_ERR;

    if (this->program.load(vertexshader, fragmentshader)) return STATUS_ERR;

    vertexshader.destroy();
    fragmentshader.destroy();

    this->vao.create();
    this->vao.bind();

    this->vbo.create();
    this->vbo.bind();
    this->vbo.load(vertex_buffer_data, GL_STATIC_DRAW);

    return STATUS_OK;
}

void Context::destroy()
{
    this->program.destroy();
    this->vbo.destroy();
    this->vao.destroy();
}
