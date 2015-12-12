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
    // Clear buffers when destroyed.
    this->bind();
    this->load(1024, 1024);
    this->unbind();

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
gl::Texture::load(int w, int h)
{
    unsigned char* buf = new unsigned char[w * h * 3];
    for (int i = 0; i < w * h; i++)
    {
        buf[i * 3 + 0] = (unsigned char)255;
        buf[i * 3 + 1] = (unsigned char)255;
        buf[i * 3 + 2] = (unsigned char)255;
    }
    this->upload(w, h, buf);
}

void
gl::Texture::load(std::string path)
{
    std::cout << "Path: " << path << std::endl;
    FREE_IMAGE_FORMAT format;
    FIBITMAP* img;
    int w, h;

    format = FreeImage_GetFileType(path.c_str());
    img = FreeImage_Load(format, path.c_str());
    w = FreeImage_GetWidth(img);
    h = FreeImage_GetHeight(img);

    unsigned char* buf = new unsigned char[w * h * 3];
    FreeImage_ConvertToRawBits(buf, img, w * 3, 24, 0, 0, 0);
    FreeImage_Unload(img);

    this->upload(w, h, buf);
}

void
gl::Texture::upload(int w, int h, unsigned char* buf)
{
    std::cout << "Loaded texture. Dimensions: (" << w << ", " << h << ")" << std::endl;
    glTexImage2D(
        this->m_type, // GL_TEXTURE_2D
        0,            // mipmap level
        GL_RGB,       // internal format
        w, h, 0,      // width, height, border
        GL_BGR,       // format
        GL_UNSIGNED_BYTE, // data type
        buf
    );
    glTexParameteri(this->m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(this->m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    delete[] buf;
}

GLuint
gl::Texture::getId()
{
    return this->m_tex;
}
