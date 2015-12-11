#include "context.h"

// An array of 3 vectors which represents 3 vertices
const std::vector<glm::vec3> vertex_buffer_data({
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f,  1.0f, 0.0f),
});

Context::Context()
{
}

Context::~Context()
{
    this->destroy();
    for (auto vao : vao_array)
    {
        vao->destroy();
        delete vao;
    }
    for (auto texture : textures)
    {
        texture->destroy();
        delete texture;
    }
}

Status Context::create(std::vector<tinyobj::shape_t> shapes,
                       std::vector<tinyobj::material_t> materials)
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

    for (auto shape : shapes)
    {
        vao_array.push_back(this->create(shape));
    }

    for (auto material : materials)
    {
        this->textures.push_back(this->create(material));
    }

    return STATUS_OK;
}

VertexArray* Context::create(tinyobj::shape_t shape)
{
    VertexArray* vao = new VertexArray;
    VertexBuffer vbo_index(GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo(GL_ARRAY_BUFFER);
    VertexBuffer uv(GL_ARRAY_BUFFER);

    vao->create();
    vao->bind();

    vbo_index.create();
    vbo_index.bind();
    vbo_index.load(shape.mesh.indices, GL_STATIC_DRAW);

    vbo.create();
    vbo.bind();
    vbo.load(shape.mesh.positions, GL_STATIC_DRAW);
    vao->bindvertexattrib();

    uv.create();
    uv.bind();
    uv.load(shape.mesh.texcoords, GL_STATIC_DRAW);
    vao->binduvattrib();

    vao->m_size = vbo_index.size();
    vao->texture_idx = shape.mesh.material_ids.front();
    vao->unbind();

    vbo_index.unbind();
    vbo.unbind();
    uv.unbind();

    return vao;
}

Texture* Context::create(tinyobj::material_t material)
{
    Texture* texture = new Texture(GL_TEXTURE_2D);
    texture->create();
    texture->bind();
    texture->load("../Desmond_Miles/" + material.diffuse_texname);
    texture->unbind();

    return texture;
}

void Context::destroy()
{
    this->program.destroy();
}

void Context::draw(Camera& camera)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->program.use();
    this->program["mvp"].set(mvp);

    for (auto vao : vao_array)
    {
        this->textures[vao->texture_idx]->bind();
        this->program["tex"].set(GL_TEXTURE0);

        vao->bind();

        glDrawElements(
            GL_TRIANGLES,            // mode
            vao->m_size,             // count
            GL_UNSIGNED_INT,         // type
            (void*)0                 // element array buffer offset
        );

        vao->unbind();
    }
}
