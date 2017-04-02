#include "uniform.h"

void
graphics::gl::Uniform::set(glm::mat4& uniform) const
{
    glUniformMatrix4fv(this->location, 1, GL_FALSE, &uniform[0][0]);
    check("Error setting glm::mat4 uniform.");
}

void
graphics::gl::Uniform::set(unsigned texture) const
{
    glUniform1i(this->location, texture);
    check("Error setting texture uniform.");
}
