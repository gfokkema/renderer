#ifndef GL_TEXTURE_H_
#define GL_TEXTURE_H_

#include "common.h"

#include "gl.h"

namespace gl
{

typedef struct image_buffer
{
    int w, h;
    std::vector<unsigned char> data;
    unsigned size() { return w * h * 3; };
} image_buffer;

class Texture : public Gl
{
public:
    Texture(GLenum type);
    ~Texture();

    void bind() const;

    void upload(std::shared_ptr<image_buffer>) const;
    void unbind() const;
private:
    GLenum m_type;
};

}

#endif /* GL_TEXTURE_H_ */
