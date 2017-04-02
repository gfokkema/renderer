#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include "common.h"

#include "gl.h"

namespace gl
{

class VertexArray : public Gl {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void binduvattrib() const;
    void bindvertexattrib() const;
    void unbindattrib() const;

    unsigned m_size;
    GLuint texture_idx;
private:
};

}

#endif /* __VERTEXARRAY_H */
