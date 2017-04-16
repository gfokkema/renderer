#ifndef GL_UNIFORM_H_
#define GL_UNIFORM_H_

#include "common.h"

namespace graphics { namespace gl {

class Uniform {
public:
    void set(glm::mat4&) const;
    void set(unsigned texture) const;
    void set(std::vector<unsigned>& texture) const;

    Uniform operator[](unsigned idx) const;
    friend std::ostream& operator<<(std::ostream& os, const graphics::gl::Uniform& uniform);

    std::string name;
    GLuint location;
    GLenum type;
    int size;
};

std::ostream& operator<<(std::ostream& os, const graphics::gl::Uniform& uniform);

} }

#endif /* GL_UNIFORM_H_ */
