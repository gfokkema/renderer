#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include "common.h"

#include "gl.h"

namespace gl
{

class Shader : public Gl {
public:
    Shader(GLenum type);
    ~Shader();

    void load(std::string path) const;
private:
    void read(std::string path) const;
    void compile() const;

    GLenum m_type;
};

}

#endif /* GL_SHADER_H_ */
