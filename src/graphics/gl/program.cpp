#include "program.h"

graphics::gl::Program::Program()
{
    this->getId() = glCreateProgram();
    check("Error creating program.");
}

graphics::gl::Program::~Program()
{
    fmt::print("Destroying program.\n");
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
    fmt::print("Linking program.\n");
    glLinkProgram(this->getId());

    // Check the program
    glGetProgramiv(this->getId(), GL_LINK_STATUS, &result);
    glGetProgramiv(this->getId(), GL_INFO_LOG_LENGTH, &log_size);
    glValidateProgram(this->getId());
    if (log_size > 1) {
        std::vector<char> program_log(log_size + 1);
        glGetProgramInfoLog(this->getId(), log_size, NULL, &program_log.front());
        fmt::print("{}\n", program_log[0]);
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
    fmt::print("Found {} uniforms.\n", no_uniform);

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
    fmt::print("Program uniforms:\n");
    for (auto uniform : this->m_uniforms)
        fmt::print("  ({}, {})\n", uniform.first, uniform.second);
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
