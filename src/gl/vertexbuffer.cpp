#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(GLenum type)
: created(false), m_vbo(0), m_type(type), m_size(0)
{
}

VertexBuffer::~VertexBuffer()
{
    this->destroy();
}

void VertexBuffer::create()
{
    this->created = true;

    glGenBuffers(1, &this->m_vbo);
}

void VertexBuffer::destroy()
{
    glDeleteBuffers(1, &this->m_vbo);
}

void VertexBuffer::bind()
{
    if (!this->created) this->create();

    glBindBuffer(this->m_type, this->m_vbo);
}

void VertexBuffer::unbind()
{
    glBindBuffer(this->m_type, 0);
}

void VertexBuffer::load(std::vector<float> data, GLenum usage)
{
    this->bind();

    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(float) * data.size(), &data.front(), usage);
}

void VertexBuffer::load(std::vector<unsigned> data, GLenum usage)
{
    this->bind();

    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(unsigned) * data.size(), &data.front(), usage);
}

//void VertexBuffer::load(std::vector<glm::vec3> data, GLenum usage)
//{
//    this->bind();
//
//    this->m_size = data.size();
//    glBufferData(this->m_type, sizeof(glm::vec3) * data.size(), &data.front(), usage);
//}

unsigned VertexBuffer::size()
{
    return this->m_size;
}

GLuint VertexBuffer::getId()
{
    return this->m_vbo;
}
