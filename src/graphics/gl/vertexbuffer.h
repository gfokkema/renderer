#ifndef __VERTEXBUFFER_H
#define __VERTEXBUFFER_H

#include "common.h"

#include "gl_base.h"

namespace graphics { namespace gl {

class VertexBuffer : public Gl {
public:
    VertexBuffer(GLenum type);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    template<typename T>
    void upload(const std::vector<T>&, GLenum usage);

    unsigned size() const;
private:
    GLenum m_type;
    unsigned m_size;
};

} }

#endif /* __VERTEXBUFFER_H */

