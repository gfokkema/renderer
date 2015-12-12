#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "common.h"

#include "shader.h"
#include "uniform.h"

namespace gl
{

typedef std::pair<std::string, Uniform> entry;

class Program {
public:
    Program();
    ~Program();

    void create();
    void destroy();

    Status load(Shader, Shader);

    void attach(Shader);
    void detach(Shader);
    Status link();
    void resolve();

    void use();
    Uniform operator[](std::string);

    GLuint getId();
private:
    GLuint m_program;

    std::map<std::string, Uniform> m_uniforms;
};

}

#endif /* __PROGRAM_H */
