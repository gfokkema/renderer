#include "vertexarray.h"

VertexArray::VertexArray()
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
