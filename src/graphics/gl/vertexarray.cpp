#include "vertexarray.h"

graphics::gl::VertexArray::VertexArray()
: m_size(0), texture_idx(0)
{
    glGenVertexArrays(1, &this->getId());
    check("Error creating vertexarray.");
}

graphics::gl::VertexArray::~VertexArray()
{
    fmt::print("Destroying vao.\n");
    glDeleteVertexArrays(1, &this->getId());
    check("Error deleting vertexarray.");
}

void
graphics::gl::VertexArray::bind() const
{
    glBindVertexArray(this->getId());
    check("Error binding vertexarray.");
}

void
graphics::gl::VertexArray::unbind() const
{
    glBindVertexArray(0);
    check("Error unbinding vertexarrays.");
}

void
graphics::gl::VertexArray::bindattrib(unsigned pos, unsigned elemcount, GLenum type) const
{
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(
       pos,       // attribute 0
       elemcount, // size
       type,      // type
       GL_FALSE,  // normalized?
       0,         // stride
       (void*)0   // array buffer offset
    );
    check("Error binding vertexarray attrib.");
}

void
graphics::gl::VertexArray::unbindattrib(unsigned pos) const
{
    glDisableVertexAttribArray(pos);
    check("Error unbinding attribs[" + std::to_string(pos) + "].");
}
