#include "context.h"

// An array of 3 vectors which represents 3 vertices
const std::vector<glm::vec3> vertex_buffer_data({
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f,  1.0f, 0.0f),
});

Context::Context()
: uv(GL_ARRAY_BUFFER), vbo(GL_ARRAY_BUFFER), vbo_index(GL_ELEMENT_ARRAY_BUFFER),
  texture(GL_TEXTURE_2D), texture2(GL_TEXTURE_2D)
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

    this->uv.create();
    this->uv.bind();
    this->vao.binduvattrib();

    this->vbo.create();
    this->vbo.bind();
    this->vbo_index.create();
    this->vbo_index.bind();
    this->vao.bindvertexattrib();

    this->vao.unbind();
    this->vbo.unbind();
    this->vbo_index.unbind();

    this->texture.create();
    this->texture.bind();
    this->texture.load("../debug_texture.jpg");
    this->texture.unbind();

    this->texture2.create();
    this->texture2.bind();
    this->texture2.load(512, 512);
    this->texture2.unbind();

    return STATUS_OK;
}

void Context::destroy()
{
    this->program.destroy();
    this->vao.destroy();
    this->vbo.destroy();
    this->vbo_index.destroy();
    this->texture.destroy();
}

void Context::draw(Camera& camera, std::vector<tinyobj::shape_t> shapes)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->program.use();
    this->program["mvp"].set(mvp);
    this->program["tex"].set(texture);

    this->vao.bind();
    for (auto shape : shapes)
    {
        this->uv.bind();
        this->uv.load(shape.mesh.texcoords, GL_STATIC_DRAW);
        this->vbo.bind();
        this->vbo.load(shape.mesh.positions, GL_STATIC_DRAW);
        this->vbo_index.bind();
        this->vbo_index.load(shape.mesh.indices, GL_STATIC_DRAW);

        glDrawElements(
            GL_TRIANGLES,            // mode
            this->vbo_index.size(),  // count
            GL_UNSIGNED_INT,         // type
            (void*)0                 // element array buffer offset
        );
    }
    this->vao.unbind();
    this->vbo.unbind();
    this->vbo_index.unbind();
    this->texture.unbind();
}
