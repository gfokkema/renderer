#include "context.h"

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
        this->vao_array.push_back(this->create(shape));
    }

    for (auto idx = 0; idx < materials.size(); idx++)
    {
        glActiveTexture(GL_TEXTURE0 + idx);

        this->textures.push_back(this->create(materials[idx]));
    }

    return STATUS_OK;
}

VertexArray* Context::create(tinyobj::shape_t shape)
{
    VertexArray* vao = new VertexArray;
    VertexBuffer vbo_index(GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo(GL_ARRAY_BUFFER);
    VertexBuffer uv(GL_ARRAY_BUFFER);

    vao->bind();

    vbo_index.bind();
    vbo_index.load<unsigned>(shape.mesh.indices, GL_STATIC_DRAW);

    vbo.bind();
    vbo.load<float>(shape.mesh.positions, GL_STATIC_DRAW);
    vao->bindvertexattrib();

    uv.bind();
    uv.load<float>(shape.mesh.texcoords, GL_STATIC_DRAW);
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
        this->program["tex"].set(vao->texture_idx);

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
