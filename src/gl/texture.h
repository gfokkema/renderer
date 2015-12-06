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

    void load(int, int);
    void load(std::string);
    void unbind();

    GLuint getId();
private:
    void upload(int, int, unsigned char*);
    GLuint m_tex;
    GLenum m_type;
};

#endif /* GL_TEXTURE_H_ */
