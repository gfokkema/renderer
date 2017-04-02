#include "vertexbuffer.h"

template void gl::VertexBuffer::upload<float>(const std::vector<float>&, GLenum);
template void gl::VertexBuffer::upload<unsigned>(const std::vector<unsigned>&, GLenum);

gl::VertexBuffer::VertexBuffer(GLenum type)
: m_type(type), m_size(0)
{
    glGenBuffers(1, &this->getId());
    check("Error creating vertex buffer.");
}

gl::VertexBuffer::~VertexBuffer()
{
    std::cout << "Destroying vbo." << std::endl;
    glDeleteBuffers(1, &this->getId());
    check("Error deleting vertex buffer.");
}

void
gl::VertexBuffer::bind() const
{
    glBindBuffer(this->m_type, this->getId());
    check("Error binding vertex buffer.");
}

void
gl::VertexBuffer::unbind() const
{
    glBindBuffer(this->m_type, 0);
    check("Error unbinding vertex buffers.");
}

template<typename T>
void
gl::VertexBuffer::upload(const std::vector<T>& data, GLenum usage)
{
    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(T) * data.size(), &data.front(), usage);
    check("Error uploading to vertex buffer.");
}

unsigned
gl::VertexBuffer::size() const
{
    return this->m_size;
}
