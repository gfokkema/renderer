#include "vertexbuffer.h"

template void gl::VertexBuffer::upload<float>(std::vector<float>, GLenum);
template void gl::VertexBuffer::upload<unsigned>(std::vector<unsigned>, GLenum);

gl::VertexBuffer::VertexBuffer(GLenum type)
: m_vbo(0), m_type(type), m_size(0), m_created(false)
{
}

gl::VertexBuffer::~VertexBuffer()
{
//    this->destroy();
}

void
gl::VertexBuffer::create()
{
    this->m_created = true;

    glGenBuffers(1, &this->m_vbo);
}

void
gl::VertexBuffer::destroy()
{
    std::cout << "Destroying vbo." << std::endl;
    glDeleteBuffers(1, &this->m_vbo);
}

void
gl::VertexBuffer::bind()
{
    if (!this->m_created) create();

    glBindBuffer(this->m_type, this->m_vbo);
}

void
gl::VertexBuffer::unbind()
{
    glBindBuffer(this->m_type, 0);
}

template<typename T>
void
gl::VertexBuffer::upload(std::vector<T> data, GLenum usage)
{
    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(T) * data.size(), &data.front(), usage);
}

unsigned
gl::VertexBuffer::size()
{
    return this->m_size;
}

GLuint
gl::VertexBuffer::getId()
{
    return this->m_vbo;
}
