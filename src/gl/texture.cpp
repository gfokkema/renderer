#include "texture.h"

#include <FreeImage.h>

gl::Texture::Texture(GLenum type)
: m_type(type)
{
    glGenTextures(1, &this->m_tex);
    check("Error creating texture.");
}

gl::Texture::~Texture()
{
    glDeleteTextures(1, &this->m_tex);
    check("Error deleting texture.");
}

void
gl::Texture::bind()
{
    glBindTexture(this->m_type, this->m_tex);
    check("Error binding texture.");
}

void
gl::Texture::unbind()
{
    glBindTexture(this->m_type, 0);
    check("Error unbinding textures.");
}

void
gl::Texture::upload(image_buffer img)
{
    std::cout << "Loaded texture. Dimensions: (" << img.w << ", " << img.h << ")" << std::endl;
    glTexImage2D(
        this->m_type,     // GL_TEXTURE_2D
        0,                // mipmap level
        GL_RGB,           // internal format
        img.w, img.h, 0,  // width, height, border
        GL_BGR,           // format
        GL_UNSIGNED_BYTE, // data type
        img.data.data()
    );
    glTexParameteri(this->m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(this->m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    check("Error uploading texture.");
}

GLuint
gl::Texture::getId()
{
    return this->m_tex;
}
