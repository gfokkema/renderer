#ifndef __VERTEXARRAY_H
#define __VERTEXARRAY_H

#include "common.h"

#include "gl_base.h"

namespace graphics { namespace gl {

class VertexArray : public Gl {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void bindattrib(unsigned pos, unsigned elemcount, GLenum type) const;
    void unbindattrib(unsigned pos) const;

    unsigned m_size;
    GLuint texture_idx;
private:
};

} }

#endif /* __VERTEXARRAY_H */
