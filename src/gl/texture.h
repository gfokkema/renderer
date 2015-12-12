#ifndef GL_TEXTURE_H_
#define GL_TEXTURE_H_

#include "common.h"

namespace gl
{

typedef struct image_buffer
{
    int w, h;
    std::vector<unsigned char> data;
} image_buffer;

class Texture
{
public:
    Texture(GLenum type);
    ~Texture();

    void create();
    void destroy();

    void bind();

    void upload(image_buffer);
    void unbind();

    GLuint getId();
private:
    bool m_created;
    GLuint m_tex;
    GLenum m_type;
};

}

#endif /* GL_TEXTURE_H_ */
