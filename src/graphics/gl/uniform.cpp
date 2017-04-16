#include "uniform.h"

std::ostream&
graphics::gl::operator<<(std::ostream& os, const Uniform& uniform)
{
    os << "[name: \"" << uniform.name << "\","
       << " location: \"" << uniform.location << "\","
       << " type: \"" << std::hex << uniform.type << "\","
       << " size: \"" << std::dec << uniform.size << "\"]";
    return os;
}

graphics::gl::Uniform::Uniform(unsigned program, std::string name, GLenum type, int size)
: name(name.substr(0, name.rfind("[0]"))), type(type), size(size) {
    location = glGetUniformLocation(program, this->name.c_str());

    uniforms.push_back(*this);
    for (auto i = 1; i < size; i++) {
        Uniform uniform(program, fmt::format("{}[{}]", this->name, i), type, 1);
        uniforms.push_back(uniform);
    }
}

graphics::gl::Uniform::~Uniform()
{
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

const graphics::gl::Uniform&
graphics::gl::Uniform::operator[](unsigned idx) const
{
    if (idx >= this->size)
        throw new BaseException("Index out of range");

    return uniforms[idx];
}
