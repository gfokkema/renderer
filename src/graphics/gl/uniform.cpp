#include "uniform.h"

std::ostream&
graphics::gl::operator<<(std::ostream& os, const graphics::gl::Uniform& uniform)
{
    os << "[name: \"" << uniform.name << "\","
       << " location: \"" << uniform.location << "\","
       << " type: \"" << std::hex << uniform.type << "\","
       << " size: \"" << std::dec << uniform.size << "\"]";
    return os;
}

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

void
graphics::gl::Uniform::set(std::vector<unsigned>& textures) const
{
    for (auto& i : textures) {
        glUniform1i(this->location, i);
        check("Error setting texture uniform.");
    }
}

graphics::gl::Uniform
graphics::gl::Uniform::operator[](unsigned idx) const
{
    if (idx >= this->size)
        throw new BaseException("Index out of range");

    Uniform temp;
    temp.location = this->location;
    temp.name = fmt::format("{0}[{1}]", this->name, idx);
    return temp;
}
