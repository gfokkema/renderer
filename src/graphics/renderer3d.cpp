#include "renderer3d.h"

#include "util/file.h"

graphics::Renderer3D::Renderer3D()
: vertexshader(GL_VERTEX_SHADER),
  fragmentshader(GL_FRAGMENT_SHADER),
  program(),
  m_vao(),
  m_vbo(GL_ARRAY_BUFFER),
  m_ibo(GL_ELEMENT_ARRAY_BUFFER)
{
    vertexshader.load(util::File("../src/shaders/shader.vertex.c").read());
    fragmentshader.load(util::File("../src/shaders/shader.fragment.c").read());

    program.load(vertexshader, fragmentshader);
    program.resolve();

    m_vao.bind();
    m_vbo.bind(); // TODO: Allocate space beforehand?
    m_vao.bindattrib(0, 3, GL_FLOAT,          sizeof(gl::VertexData), 0);
    m_vao.bindattrib(1, 2, GL_FLOAT,          sizeof(gl::VertexData), offsetof(gl::VertexData, uv));
    m_vao.bindiattrib(2, 1, GL_UNSIGNED_SHORT, sizeof(gl::VertexData), offsetof(gl::VertexData, tex));

    m_ibo.bind(); // TODO: Allocate space beforehand?

    m_vao.unbind();
    m_vbo.unbind();
    m_ibo.unbind();
}

graphics::Renderer3D::~Renderer3D()
{
}

void
graphics::Renderer3D::submit(std::vector<renderable_ptr>& renderables)
{
    for (auto& renderable : (std::vector<adv_renderable_ptr>&)renderables)
    {
        unsigned offset = m_vertexdata.size();

        // consolidate vertex and index data into one big buffer here
        for (auto& vertex : renderable->data()) {
            m_vertexdata.push_back(vertex);
        }

        for (auto& index : renderable->index()) {
            m_indexdata.push_back(offset + index);
        }
    }
}

void
graphics::Renderer3D::submit(image_buffer_ptr& buffer)
{
    unsigned unit = this->m_textures.size();
    glActiveTexture(GL_TEXTURE0 + unit);

    auto texture = std::make_unique<gl::Texture>(GL_TEXTURE_2D);
    texture->bind();
    texture->upload(buffer);

    program.use();
    program["tex"][unit].set(unit);

    this->m_textures.push_back(std::move(texture));
}

void
graphics::Renderer3D::draw(Camera& camera)
{
    m_vbo.bind();
    m_vbo.upload<gl::VertexData>(m_vertexdata, GL_STATIC_DRAW);

    m_ibo.bind();
    m_ibo.upload<unsigned>(m_indexdata, GL_STATIC_DRAW);

    auto model = glm::mat4(1.0f);
    auto mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.use();
    program["mvp"].set(mvp);

    m_vao.bind();
    glDrawElements(
        GL_TRIANGLES,    // mode
        m_ibo.size(),    // count
        GL_UNSIGNED_INT, // type
        (void*)0         // element array buffer offset
    );
    m_vao.unbind();

    m_vertexdata.clear();
    m_indexdata.clear();
}
