#include "context.h"

gl::Context::Context(const util::ObjModel & model)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    gl::Shader vertexshader(GL_VERTEX_SHADER);
    gl::Shader fragmentshader(GL_FRAGMENT_SHADER);

    vertexshader.load("../src/shaders/shader.vertex.c");
    fragmentshader.load("../src/shaders/shader.fragment.c");
    this->program.load(vertexshader, fragmentshader);
    this->program.resolve();

    for (auto shape : model.m_shapes)
    {
        this->create(shape);
    }

    for (auto idx = 0; idx < model.m_materials.size(); idx++)
    {
        auto mat = model.m_materials.begin() + idx;
        glActiveTexture(GL_TEXTURE0 + idx);

        auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
        texture->bind();
        texture->upload(mat->get_buffer(util::IMAGE_MAP::DIFFUSE));

        this->textures.push_back(texture);
    }
}

void
gl::Context::create(const tinyobj::shape_t & shape)
{
    auto vao       = std::make_shared<VertexArray>();
    auto vbo_index = std::make_shared<VertexBuffer>(GL_ELEMENT_ARRAY_BUFFER);
    auto vbo       = std::make_shared<VertexBuffer>(GL_ARRAY_BUFFER);
    auto uv        = std::make_shared<VertexBuffer>(GL_ARRAY_BUFFER);

    this->vao_array.push_back(vao);
    this->vbo_array.push_back(vbo_index);
    this->vbo_array.push_back(vbo);
    this->vbo_array.push_back(uv);

    vao->bind();

    vbo_index->bind();
    vbo_index->upload<unsigned>(shape.mesh.indices, GL_STATIC_DRAW);

    vbo->bind();
    vbo->upload<float>(shape.mesh.positions, GL_STATIC_DRAW);
    vao->bindvertexattrib();

    uv->bind();
    uv->upload<float>(shape.mesh.texcoords, GL_STATIC_DRAW);
    vao->binduvattrib();

    // FIXME: These attributes should not be part of the vao.
    //        Might consider mirroring opengl vbo binding state though.
    vao->m_size = vbo_index->size();
    vao->texture_idx = shape.mesh.material_ids.front();
    vao->unbind();

    vbo_index->unbind();
    vbo->unbind();
    uv->unbind();
}

gl::Context::~Context()
{
}

// FIXME: Camera should be const, but camera.matrix() updates stuff.
//        Might therefore move updating the camera into the main render loop.
void
gl::Context::draw(util::Camera & camera)
{
    auto model = glm::mat4(1.0f);
    auto mvp = camera.matrix() * model;

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
