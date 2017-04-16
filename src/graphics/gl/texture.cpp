#include "texture.h"

graphics::gl::Texture::Texture(GLenum type)
: m_type(type)
{
    glGenTextures(1, &this->getId());
    check("Error creating texture.");
}

graphics::gl::Texture::~Texture()
{
    fmt::print("Destroying texture.\n");
    glDeleteTextures(1, &this->getId());
    check("Error deleting texture.");
}

void
graphics::gl::Texture::bind() const
{
    glBindTexture(this->m_type, this->getId());
    check("Error binding texture.");
}

void
graphics::gl::Texture::unbind() const
{
    glBindTexture(this->m_type, 0);
    check("Error unbinding textures.");
}

void
graphics::gl::Texture::upload(std::shared_ptr<image_buffer> img) const
{
    fmt::print("Loaded texture. Dimensions: ({}, {})\n", img->w, img->h);
    glTexImage2D(
        this->m_type,     // GL_TEXTURE_2D
        0,                // mipmap level
        GL_RGB,           // internal format
        img->w, img->h, 0,// width, height, border
        GL_BGR,           // format
        GL_UNSIGNED_BYTE, // data type
        img->data.data()
    );
    glTexParameteri(this->m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(this->m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    check("Error uploading texture.");
}
