#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "common.h"

#include "gl_base.h"
#include "shader.h"
#include "uniform.h"

namespace graphics { namespace gl {

typedef std::pair<std::string, Uniform> entry;

class Program : public Gl {
public:
    Program();
    ~Program();

    void load(Shader&, Shader&) const;
    void resolve();
    void use() const;
    Uniform operator[](std::string) const;
private:
    void attach(Shader&) const;
    void detach(Shader&) const;
    void link() const;

    std::map<std::string, Uniform> m_uniforms;
};

} }

#endif /* __PROGRAM_H */
