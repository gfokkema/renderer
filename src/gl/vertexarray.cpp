#include "vertexarray.h"

VertexArray::VertexArray()
: m_vao(0)
{
}

VertexArray::~VertexArray()
{
    this->destroy();
}

void VertexArray::create()
{
    glGenVertexArrays(1, &this->m_vao);
}

void VertexArray::destroy()
{
    glDeleteVertexArrays(1, &this->m_vao);
}

void VertexArray::bind()
{
    glBindVertexArray(this->m_vao);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::bindattrib()
{
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

void VertexArray::unbindattrib()
{
    glDisableVertexAttribArray(0);
}

GLuint VertexArray::getId()
{
    return this->m_vao;
}
