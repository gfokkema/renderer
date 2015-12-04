#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(GLenum type)
: m_vbo(0), m_type(type)
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
    glBindBuffer(this->m_type, this->m_vbo);
}

void VertexBuffer::load(std::vector<float> data, GLenum usage)
{
    glBufferData(this->m_type, sizeof(float) * data.size(), &data.front(), usage);
}

GLuint VertexBuffer::getId()
{
    return this->m_vbo;
}
