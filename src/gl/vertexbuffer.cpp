#include "vertexbuffer.h"

template void VertexBuffer::load<float>(std::vector<float>, GLenum);
template void VertexBuffer::load<unsigned>(std::vector<unsigned>, GLenum);

VertexBuffer::VertexBuffer(GLenum type)
: m_vbo(0), m_type(type), m_size(0), m_created(false)
{
}

VertexBuffer::~VertexBuffer()
{
//    this->destroy();
}

void VertexBuffer::create()
{
    this->m_created = true;

    glGenBuffers(1, &this->m_vbo);
}

void VertexBuffer::destroy()
{
    std::cout << "Destroying vbo." << std::endl;
    glDeleteBuffers(1, &this->m_vbo);
}

void VertexBuffer::bind()
{
    if (!this->m_created) create();

    glBindBuffer(this->m_type, this->m_vbo);
}

void VertexBuffer::unbind()
{
    glBindBuffer(this->m_type, 0);
}

template<typename T>
void VertexBuffer::load(std::vector<T> data, GLenum usage)
{
    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(T) * data.size(), &data.front(), usage);
}

unsigned VertexBuffer::size()
{
    return this->m_size;
}

GLuint VertexBuffer::getId()
{
    return this->m_vbo;
}
