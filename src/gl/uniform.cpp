#include "uniform.h"

void
gl::Uniform::set(glm::mat4& uniform)
{
    glUniformMatrix4fv(this->location, 1, GL_FALSE, &uniform[0][0]);
}

void
gl::Uniform::set(unsigned texture)
{
    glUniform1i(this->location, texture);
}
