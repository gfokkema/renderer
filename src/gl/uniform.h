#ifndef GL_UNIFORM_H_
#define GL_UNIFORM_H_

#include "common.h"
#include "texture.h"

class Uniform {
public:
    void set(glm::mat4&);
    void set(GLenum texture);

    std::string name;
    GLuint location;
    GLenum type;
    int size;
};

#endif /* GL_UNIFORM_H_ */
