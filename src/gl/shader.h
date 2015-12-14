#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include "common.h"

namespace gl
{

class Shader {
public:
    Shader(GLenum type);
    ~Shader();

    void load(std::string path);

    void read(std::string path);
    void compile();

    GLuint getId();
private:
    GLuint m_shader;
    GLenum m_type;
};

}

#endif /* GL_SHADER_H_ */
