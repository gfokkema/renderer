#ifndef __VERTEXBUFFER_H
#define __VERTEXBUFFER_H

#include <GL/glew.h>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
    void create();
    void destroy();
    void bind();
    GLuint getId();
private:
    GLuint m_vbo;
};

#endif /* __VERTEXBUFFER_H */

