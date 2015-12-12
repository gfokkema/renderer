#include "vertexarray.h"

VertexArray::VertexArray()
: m_vao(0), m_size(0), texture_idx(0), m_created(false)
{
}

VertexArray::~VertexArray()
{
//    this->destroy();
}

void VertexArray::create()
{
    this->m_created = true;

    glGenVertexArrays(1, &this->m_vao);
}

void VertexArray::destroy()
{
    std::cout << "Destroying vao." << std::endl;
    glDeleteVertexArrays(1, &this->m_vao);
}

void VertexArray::bind()
{
    if (!this->m_created) create();

    glBindVertexArray(this->m_vao);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::bindvertexattrib()
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
}

void VertexArray::binduvattrib()
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
}

void VertexArray::unbindattrib()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

GLuint VertexArray::getId()
{
    return this->m_vao;
}
