#include "vertexbuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
    this->destroy();
}

void VertexBuffer::create()
{
    glGenBuffers(1, &this->m_vbo);
}

void VertexBuffer::destroy()
{
    glDeleteBuffers(1, &this->m_vbo);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
}

void VertexBuffer::setdata(GLenum target, std::vector<float> data, GLenum usage)
{
    glBufferData(target, sizeof(float) * data.size(), &data[0], usage);
}

GLuint VertexBuffer::getId()
{
    return this->m_vbo;
}
