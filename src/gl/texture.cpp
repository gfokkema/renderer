#include "texture.h"

#include <FreeImage.h>

gl::Texture::Texture(GLenum type)
: m_tex(0), m_type(type), m_created(false)
{
}

gl::Texture::~Texture()
{
//    this->destroy();
}

void
gl::Texture::create()
{
    this->m_created = true;

    glGenTextures(1, &this->m_tex);
}

void
gl::Texture::destroy()
{
    glDeleteTextures(1, &this->m_tex);
}

void
gl::Texture::bind()
{
    if (!this->m_created) create();

    glBindTexture(this->m_type, this->m_tex);
}

void
gl::Texture::unbind()
{
    glBindTexture(this->m_type, 0);
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
}

GLuint
gl::Texture::getId()
{
    return this->m_tex;
}
