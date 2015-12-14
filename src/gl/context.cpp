#include "context.h"

gl::Context::Context(util::ObjModel model)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    gl::Shader vertexshader(GL_VERTEX_SHADER);
    gl::Shader fragmentshader(GL_FRAGMENT_SHADER);

    vertexshader.load("../src/shaders/shader.vertex.c");
    fragmentshader.load("../src/shaders/shader.fragment.c");
    this->program.load(vertexshader, fragmentshader);

    for (auto shape : model.m_shapes)
    {
        this->vao_array.push_back(this->create(shape));
    }

    for (auto idx = 0; idx < model.m_materials.size(); idx++)
    {
        auto mat = model.m_materials.begin() + idx;
        glActiveTexture(GL_TEXTURE0 + idx);

        Texture* texture = new Texture(GL_TEXTURE_2D);
        texture->bind();
        texture->upload(mat->get_buffer(util::IMAGE_MAP::DIFFUSE));

        this->textures.push_back(texture);
    }
}

gl::VertexArray*
gl::Context::create(tinyobj::shape_t shape)
{
    VertexArray* vao = new VertexArray;
    VertexBuffer vbo_index(GL_ELEMENT_ARRAY_BUFFER);
    VertexBuffer vbo(GL_ARRAY_BUFFER);
    VertexBuffer uv(GL_ARRAY_BUFFER);

    vao->bind();

    vbo_index.bind();
    vbo_index.upload<unsigned>(shape.mesh.indices, GL_STATIC_DRAW);

    vbo.bind();
    vbo.upload<float>(shape.mesh.positions, GL_STATIC_DRAW);
    vao->bindvertexattrib();

    uv.bind();
    uv.upload<float>(shape.mesh.texcoords, GL_STATIC_DRAW);
    vao->binduvattrib();

    // FIXME: These attributes should not be part of the vao.
    //        Might consider mirroring opengl vbo binding state though.
    vao->m_size = vbo_index.size();
    vao->texture_idx = shape.mesh.material_ids.front();
    vao->unbind();

    vbo_index.unbind();
    vbo.unbind();
    uv.unbind();

    return vao;
}

gl::Context::~Context()
{
    for (auto vao : vao_array)
    {
        delete vao;
    }
    for (auto texture : textures)
    {
        delete texture;
    }
}

void
gl::Context::draw(util::Camera& camera)
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
