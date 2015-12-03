#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include <GL/glew.h>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void create();
    void destroy();
    void bind();

    GLuint getId();
private:
    GLuint m_vao;
};

#endif /* __VERTEXARRAY_H */
