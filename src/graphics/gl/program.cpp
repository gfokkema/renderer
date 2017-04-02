#include "program.h"

std::ostream& operator<<(std::ostream& os, const graphics::gl::Uniform& uniform)
{
    os << "[name: \"" << uniform.name << "\","
       << " location: \"" << uniform.location << "\","
       << " type: \"" << std::hex << uniform.type << "\","
       << " size: \"" << std::dec << uniform.size << "\"]";
    return os;
}

graphics::gl::Program::Program()
{
    this->getId() = glCreateProgram();
    check("Error creating program.");
}

graphics::gl::Program::~Program()
{
    std::cout << "Destroying program." << std::endl;
    glDeleteProgram(this->getId());
    check("Error deleting program.");
}

void
graphics::gl::Program::load(Shader& vertex, Shader& fragment) const
{
    this->attach(vertex);
    this->attach(fragment);

    this->link();

    this->detach(vertex);
    this->detach(fragment);
}

void
graphics::gl::Program::attach(Shader& shader) const
{
    glAttachShader(this->getId(), shader.getId());
    check("Error attaching shader to program.");
}

void
graphics::gl::Program::detach(Shader& shader) const
{
    glDetachShader(this->getId(), shader.getId());
    check("Error detaching shader from program.");
}

void
graphics::gl::Program::link() const
{
    int result = 0;
    int log_size = 0;

    // Link the program
    std::cout << "Linking program." << std::endl;
    glLinkProgram(this->getId());

    // Check the program
    glGetProgramiv(this->getId(), GL_LINK_STATUS, &result);
    glGetProgramiv(this->getId(), GL_INFO_LOG_LENGTH, &log_size);
    glValidateProgram(this->getId());
    if (log_size > 1) {
        std::vector<char> program_log(log_size + 1);
        glGetProgramInfoLog(this->getId(), log_size, NULL, &program_log.front());
        std::cout << program_log[0] << std::endl;
    }

    if (result == GL_FALSE)
        throw BaseException("Error linking program.");
}

void
graphics::gl::Program::resolve()
{
    int no_uniform = 0;
    int max_name_size = 0;

    glGetProgramiv(this->getId(), GL_ACTIVE_UNIFORMS, &no_uniform);
    glGetProgramiv(this->getId(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_size);

    char buf[max_name_size];
    for (auto i = 0; i < no_uniform; i++)
    {
        Uniform uniform;

        glGetActiveUniform(this->getId(), i, max_name_size, NULL, &uniform.size, &uniform.type, buf);
        uniform.name = std::string(buf);
        uniform.location = glGetUniformLocation(this->getId(), uniform.name.c_str());

        this->m_uniforms.insert(entry(uniform.name, uniform));
    }

    // FIXME: DEBUG CODE
    std::cout << "Program uniforms:" << std::endl;
    for (auto uniform : this->m_uniforms)
    {
        std::cout << "  (" << uniform.first << ", " << uniform.second << ")" << std::endl;
    }
}

void
graphics::gl::Program::use() const
{
    glUseProgram(this->getId());
    check("Error using program.");
}

graphics::gl::Uniform
graphics::gl::Program::operator[](std::string uniform) const
{
    return this->m_uniforms.at(uniform);
}
