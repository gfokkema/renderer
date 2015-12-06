#include "texture.h"

#include <FreeImage.h>

Texture::Texture(GLenum type)
: m_tex(0), m_type(type)
{
}

Texture::~Texture()
{
    this->destroy();
}

void Texture::create()
{
    glGenTextures(1, &this->m_tex);
}

void Texture::destroy()
{
    glDeleteTextures(1, &this->m_tex);
}

void Texture::bind()
{
    glBindTexture(this->m_type, this->m_tex);
}

void Texture::unbind()
{
    glBindTexture(this->m_type, 0);
}

void Texture::load(std::string path)
{
    FREE_IMAGE_FORMAT format;
    FIBITMAP* img;
    GLubyte* texture;
    const char* cr;
    int w, h;

    format = FreeImage_GetFileType(path.c_str());
    img = FreeImage_Load(format, path.c_str());
    w = FreeImage_GetWidth(img);
    h = FreeImage_GetHeight(img);

    unsigned char* buf = new unsigned char[w * h * 3];
    FreeImage_ConvertToRawBits(buf, img, w * 3, 24, 0, 0, 0);
//    this->m_pixels = std::vector<unsigned char>(buf, buf + sizeof(buf));
    for (int i = 0; i < w * h * 3; i++)
    {
        buf[i] = (unsigned char)255;
        this->m_pixels.push_back((unsigned char)255);
    }

    printf("%d %d\n", this->m_pixels.front(), this->m_pixels.back());
    printf("%d %d\n", buf[0], buf[sizeof(buf) - 1]);
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
}

unsigned Texture::size()
{
    return this->m_pixels.size();
}

std::vector<unsigned char> Texture::pixels()
{
    return this->m_pixels;
}

GLuint Texture::getId()
{
    return this->m_tex;
}
