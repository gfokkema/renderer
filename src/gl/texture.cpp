#include "texture.h"

#include <FreeImage.h>

gl::Texture::Texture(GLenum type)
: m_type(type)
{
    glGenTextures(1, &this->getId());
    check("Error creating texture.");
}

gl::Texture::~Texture()
{
    std::cout << "Destroying texture." << std::endl;
    glDeleteTextures(1, &this->getId());
    check("Error deleting texture.");
}

void
gl::Texture::bind() const
{
    glBindTexture(this->m_type, this->getId());
    check("Error binding texture.");
}

void
gl::Texture::unbind() const
{
    glBindTexture(this->m_type, 0);
    check("Error unbinding textures.");
}

void
gl::Texture::upload(std::shared_ptr<image_buffer> img) const
{
    std::cout << "Loaded texture. Dimensions: (" << img->w << ", " << img->h << ")" << std::endl;
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
