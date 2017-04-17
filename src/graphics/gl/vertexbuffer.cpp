#include "vertexbuffer.h"

template void graphics::gl::VertexBuffer::upload<float>(const std::vector<float>&, GLenum);
template void graphics::gl::VertexBuffer::upload<unsigned>(const std::vector<unsigned>&, GLenum);
template void graphics::gl::VertexBuffer::upload<graphics::gl::VertexData>(const std::vector<VertexData>&, GLenum);

graphics::gl::VertexBuffer::VertexBuffer(GLenum type)
: m_type(type), m_size(0)
{
    glGenBuffers(1, &this->getId());
    check("Error creating vertex buffer.");
}

graphics::gl::VertexBuffer::~VertexBuffer()
{
    fmt::print("Destroying vbo.\n");
    glDeleteBuffers(1, &this->getId());
    check("Error deleting vertex buffer.");
}

void
graphics::gl::VertexBuffer::bind() const
{
    glBindBuffer(this->m_type, this->getId());
    check("Error binding vertex buffer.");
}

void
graphics::gl::VertexBuffer::unbind() const
{
    glBindBuffer(this->m_type, 0);
    check("Error unbinding vertex buffers.");
}

template<typename T>
void
graphics::gl::VertexBuffer::upload(const std::vector<T>& data, GLenum usage)
{
    this->m_size = data.size();
    glBufferData(this->m_type, sizeof(T) * data.size(), &data.front(), usage);
    check("Error uploading to vertex buffer.");
}

unsigned
graphics::gl::VertexBuffer::size() const
{
    return this->m_size;
}
