#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include "common.h"

class Shader {
public:
    Shader(GLenum type);
    ~Shader();

    void create();
    void destroy();

    Status load(std::string path);
    Status compile();

    GLuint getId();
private:
    GLuint m_shader;
    GLenum m_type;
};

#endif /* GL_SHADER_H_ */
