#include "context.h"

// An array of 3 vectors which represents 3 vertices
const std::vector<glm::vec3> vertex_buffer_data({
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f,  1.0f, 0.0f),
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

    this->vao.bindattrib();
    this->vao.unbind();
    this->vbo.unbind();

    return STATUS_OK;
}

void Context::destroy()
{
    this->program.destroy();
    this->vbo.destroy();
    this->vao.destroy();
}

void Context::draw(Camera& camera)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao.bind();
    program.use();
    program["mvp"].set(mvp);

    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data.size());

    vao.unbind();
}
