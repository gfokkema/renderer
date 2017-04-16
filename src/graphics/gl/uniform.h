#ifndef GL_UNIFORM_H_
#define GL_UNIFORM_H_

#include "common.h"

namespace graphics { namespace gl {

class Uniform {
public:
    Uniform(unsigned program, std::string name, GLenum type, int size);
    ~Uniform();

    void set(glm::mat4&) const;
    void set(unsigned texture) const;
    const Uniform& operator[](unsigned idx) const;

    friend std::ostream& operator<<(std::ostream& os, const Uniform& uniform);

    std::string name;
    GLuint location;
    GLenum type;
    int size;

    std::vector<Uniform> uniforms;
};

std::ostream& operator<<(std::ostream& os, const Uniform& uniform);

} }

#endif /* GL_UNIFORM_H_ */
