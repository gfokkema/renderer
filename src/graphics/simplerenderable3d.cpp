#include "simplerenderable3d.h"

graphics::SimpleRenderable3D::SimpleRenderable3D(program_ptr& program, tinyobj::shape_t& shape, glm::vec3 pos)
: Renderable3D(pos, shape.mesh.material_ids.front()),
  m_program(program),
  m_vao(),
  m_vbo(GL_ARRAY_BUFFER),
  m_uv(GL_ARRAY_BUFFER),
  m_ibo(GL_ELEMENT_ARRAY_BUFFER)
{
    m_vao.bind();

    m_vbo.bind();
    m_vbo.upload<float>(shape.mesh.positions, GL_STATIC_DRAW);
    m_vao.bindattrib(0, 3, GL_FLOAT);

    m_uv.bind();
    m_uv.upload<float>(shape.mesh.texcoords, GL_STATIC_DRAW);
    m_vao.bindattrib(1, 2, GL_FLOAT);

    m_ibo.bind();
    m_ibo.upload<unsigned>(shape.mesh.indices, GL_STATIC_DRAW);

    // FIXME: These attributes should not be part of the vao.
    //        Might consider mirroring opengl vbo binding state though.
    m_vao.m_size = m_ibo.size();
    m_vao.unbind();

    m_vbo.unbind();
    m_uv.unbind();
    m_ibo.unbind();
}

graphics::SimpleRenderable3D::~SimpleRenderable3D()
{
}

std::shared_ptr<graphics::gl::Program>&
graphics::SimpleRenderable3D::program()
{
    return this->m_program;
}

graphics::gl::VertexArray&
graphics::SimpleRenderable3D::vao()
{
    return this->m_vao;
}
