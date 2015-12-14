#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include "common.h"

namespace gl
{

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void binduvattrib();
    void bindvertexattrib();
    void unbindattrib();

    GLuint getId();

    unsigned m_size;
    GLuint texture_idx;
private:
    GLuint m_vao;
};

}

#endif /* __VERTEXARRAY_H */
