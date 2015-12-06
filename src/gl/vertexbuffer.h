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
    void unbind();

    void load(std::vector<float>, GLenum usage);
    void load(std::vector<unsigned>, GLenum usage);
//    void load(std::vector<glm::vec3> data, GLenum usage);

    unsigned size();

    GLuint getId();
private:
    GLuint m_vbo;
    GLenum m_type;
    unsigned m_size;
};

#endif /* __VERTEXBUFFER_H */

