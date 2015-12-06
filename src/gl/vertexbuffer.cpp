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
    std::vector<glm::vec3> vertices((glm::vec3*)&data[0],
                                    (glm::vec3*)&data[data.size()]);
    this->load(vertices, usage);
}

void VertexBuffer::load(std::vector<unsigned int> data, GLenum usage)
{
    glBufferData(this->m_type, sizeof(unsigned int) * data.size(), &data.front(), usage);
}

void VertexBuffer::load(std::vector<glm::vec3> data, GLenum usage)
{
    glBufferData(this->m_type, sizeof(glm::vec3) * data.size(), &data.front(), usage);
}

void VertexBuffer::unbind()
{
    glBindBuffer(this->m_type, this->m_vbo);
}

GLuint VertexBuffer::getId()
{
    return this->m_vbo;
}
