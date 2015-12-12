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

    unsigned m_size;
    GLuint texture_idx;
private:
    bool m_created;
    GLuint m_vao;
};

#endif /* __VERTEXARRAY_H */
