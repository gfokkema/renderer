#ifndef __VERTEXBUFFER_H
#define __VERTEXBUFFER_H

#include "common.h"

namespace gl
{

class VertexBuffer {
public:
    VertexBuffer(GLenum type);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    template<typename T>
    void upload(const std::vector<T>&, GLenum usage);

    unsigned size() const;

    GLuint getId() const;
private:
    GLuint m_vbo;
    GLenum m_type;
    unsigned m_size;
};

}

#endif /* __VERTEXBUFFER_H */

