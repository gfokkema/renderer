#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include "common.h"

namespace gl
{

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void binduvattrib() const;
    void bindvertexattrib() const;
    void unbindattrib() const;

    GLuint getId() const;

    unsigned m_size;
    GLuint texture_idx;
private:
    GLuint m_vao;
};

}

#endif /* __VERTEXARRAY_H */
