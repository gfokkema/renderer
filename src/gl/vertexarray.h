#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include "common.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void create();
    void destroy();

    void bind();
    void unbind();

    void binduvattrib();
    void bindvertexattrib();
    void unbindattrib();

    GLuint getId();
private:
    GLuint m_vao;
};

#endif /* __VERTEXARRAY_H */
