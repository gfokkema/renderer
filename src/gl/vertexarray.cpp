#include "vertexarray.h"

gl::VertexArray::VertexArray()
: m_size(0), texture_idx(0)
{
    glGenVertexArrays(1, &this->getId());
    check("Error creating vertexarray.");
}

gl::VertexArray::~VertexArray()
{
    std::cout << "Destroying vao." << std::endl;
    glDeleteVertexArrays(1, &this->getId());
    check("Error deleting vertexarray.");
}

void
gl::VertexArray::bind() const
{
    glBindVertexArray(this->getId());
    check("Error binding vertexarray.");
}

void
gl::VertexArray::unbind() const
{
    glBindVertexArray(0);
    check("Error unbinding vertexarrays.");
}

void
gl::VertexArray::bindvertexattrib() const
{
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
       0,                  // attribute 0
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    check("Error binding vertexarray attrib.");
}

void
gl::VertexArray::binduvattrib() const
{
    // uv mapping for textures
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
       1,                  // attribute 1
       2,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    check("Error binding vertexarray attrib.");
}

void
gl::VertexArray::unbindattrib() const
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    check("Error unbinding vertexarray attribs.");
}
