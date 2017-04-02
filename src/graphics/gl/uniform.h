#ifndef GL_UNIFORM_H_
#define GL_UNIFORM_H_

#include "common.h"

namespace graphics { namespace gl {

class Uniform {
public:
    void set(glm::mat4&) const;
    void set(unsigned texture) const;

    std::string name;
    GLuint location;
    GLenum type;
    int size;
};

} }

#endif /* GL_UNIFORM_H_ */
