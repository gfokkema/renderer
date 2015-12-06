#ifndef GL_TEXTURE_H_
#define GL_TEXTURE_H_

#include "common.h"

class Texture {
public:
    Texture(GLenum type);
    ~Texture();

    void create();
    void destroy();

    void bind();

    void load(std::string);
    void unbind();

    unsigned size();
    std::vector<unsigned char> pixels();

    GLuint getId();
private:
    GLuint m_tex;
    GLenum m_type;
    std::vector<unsigned char> m_pixels;
};

#endif /* GL_TEXTURE_H_ */
