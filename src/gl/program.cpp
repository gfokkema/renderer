#include "program.h"

std::ostream& operator<<(std::ostream& os, const gl::Uniform& uniform)
{
    os << "[name: \"" << uniform.name << "\","
       << " location: \"" << uniform.location << "\","
       << " type: \"" << std::hex << uniform.type << "\","
       << " size: \"" << std::dec << uniform.size << "\"]";
    return os;
}

gl::Program::Program()
{
    this->m_program = glCreateProgram();
    check("Error creating program.");
}

gl::Program::~Program()
{
    glDeleteProgram(this->m_program);
    check("Error deleting program.");
}

void
gl::Program::load(Shader& vertex, Shader& fragment)
{
    this->attach(vertex);
    this->attach(fragment);

    this->link();

    this->detach(vertex);
    this->detach(fragment);

    this->resolve();
}

void
gl::Program::attach(Shader& shader)
{
    glAttachShader(this->m_program, shader.getId());
    check("Error attaching shader to program.");
}

void
gl::Program::detach(Shader& shader)
{
    glDetachShader(this->m_program, shader.getId());
    check("Error detaching shader from program.");
}

void
gl::Program::link()
{
    int result = 0;
    int log_size = 0;

    // Link the program
    std::cout << "Linking program." << std::endl;
    glLinkProgram(this->m_program);

    // Check the program
    glGetProgramiv(this->m_program, GL_LINK_STATUS, &result);
    glGetProgramiv(this->m_program, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 1) {
        std::vector<char> program_log(log_size + 1);
        glGetProgramInfoLog(this->m_program, log_size, NULL, &program_log.front());
        std::cout << program_log[0] << std::endl;
    }

    if (result == GL_FALSE)
        throw BaseException("Error linking program.");
}

void
gl::Program::resolve()
{
    int no_uniform = 0;
    int max_name_size = 0;

    glGetProgramiv(this->m_program, GL_ACTIVE_UNIFORMS, &no_uniform);
    glGetProgramiv(this->m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_size);

    char buf[max_name_size];
    for (auto i = 0; i < no_uniform; i++)
    {
        Uniform uniform;

        glGetActiveUniform(this->m_program, i, max_name_size, NULL, &uniform.size, &uniform.type, buf);
        uniform.name = std::string(buf);
        uniform.location = glGetUniformLocation(this->m_program, uniform.name.c_str());

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
gl::Program::use()
{
    glUseProgram(this->m_program);
    check("Error using program.");
}

gl::Uniform
gl::Program::operator[](std::string uniform)
{
    return this->m_uniforms[uniform];
}

GLuint
gl::Program::getId()
{
    return this->m_program;
}
