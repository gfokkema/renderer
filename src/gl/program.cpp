#include "program.h"

std::ostream& operator<<(std::ostream& os, const Uniform& uniform)
{
    os << "[" << uniform.name << ", "
       << uniform.location << ", "
       << std::hex << uniform.type << ", "
       << std::dec << uniform.size << "]";
    return os;
}

Program::Program()
: m_program(0)
{
}

Program::~Program()
{
    this->destroy();
}

void Program::create()
{
    this->m_program = glCreateProgram();
}

void Program::destroy()
{
    glDeleteProgram(this->m_program);
}

Status Program::load(Shader vertex, Shader fragment)
{
    Status result;

    this->create();

    this->attach(vertex);
    this->attach(fragment);

    result = this->link();

    this->detach(vertex);
    this->detach(fragment);

    if (result != STATUS_OK)
        return STATUS_ERR;

    this->resolve();
    return STATUS_OK;
}

void Program::attach(Shader shader)
{
    glAttachShader(this->m_program, shader.getId());
}

void Program::detach(Shader shader)
{
    glDetachShader(this->m_program, shader.getId());
}

Status Program::link()
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

    return result == GL_TRUE ? STATUS_OK : STATUS_ERR;
}

void Program::resolve()
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
    for (auto uniform : this->m_uniforms)
    {
        std::cout << "(" << uniform.first << ", " << uniform.second << ")" << std::endl;
    }
}

void Program::use()
{
    glUseProgram(this->m_program);
}

Uniform Program::operator[](std::string uniform)
{
    return this->m_uniforms[uniform];
}

GLuint Program::getId()
{
    return this->m_program;
}
