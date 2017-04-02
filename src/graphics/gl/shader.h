#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include "common.h"

#include "gl_base.h"

namespace graphics { namespace gl {

class Shader : public Gl {
public:
    Shader(GLenum type);
    ~Shader();

    void load(std::string text) const;
private:
    void read(std::string path) const;
    void compile() const;

    GLenum m_type;
};

} }

#endif /* GL_SHADER_H_ */
