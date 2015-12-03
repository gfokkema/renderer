#ifndef __VERTEXBUFFER_H
#define __VERTEXBUFFER_H

#include <GL/glew.h>

#include <vector>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void create();
    void destroy();
    void bind();
    void setdata(GLenum, std::vector<float>, GLenum);

    GLuint getId();
private:
    GLuint m_vbo;
};

#endif /* __VERTEXBUFFER_H */

