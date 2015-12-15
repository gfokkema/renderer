#include "vertexbuffer.h"

template void gl::VertexBuffer::upload<float>(std::vector<float>&, GLenum);
template void gl::VertexBuffer::upload<unsigned>(std::vector<unsigned>&, GLenum);

gl::VertexBuffer::VertexBuffer(GLenum type)
: m_type(type), m_size(0)
{
    glGenBuffers(1, &this->m_vbo);
    check("Error creating vertex buffer.");
}

gl::VertexBuffer::~VertexBuffer()
{
    std::cout << "Destroying vbo." << std::endl;
    glDeleteBuffers(1, &this->m_vbo);
    check("Error deleting vertex buffer.");
}

void
gl::VertexBuffer::bind()
{
    glBindBuffer(this->m_type, this->m_vbo);
    check("Error binding vertex buffer.");
}

void
gl::VertexBuffer::unbind()
{
    glBindBuffer(this->m_type, 0);
    check("Error unbinding vertex buffers.");
}

template<typename T>
void
gl::VertexBuffer::upload(std::vector<T>& data, GLenum usage)
{
    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(T) * data.size(), &data.front(), usage);
    check("Error uploading to vertex buffer.");
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
