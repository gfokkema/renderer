#ifndef __VERTEXBUFFER_H
#define __VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {
public:
    VertexBuffer(GLenum type);
    ~VertexBuffer();

    void create();
    void destroy();

    void bind();
    void load(std::vector<glm::vec3> data, GLenum usage);
    void unbind();

    GLuint getId();
private:
    GLuint m_vbo;
    GLenum m_type;
};

#endif /* __VERTEXBUFFER_H */

