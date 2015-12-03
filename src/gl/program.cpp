#include "program.h"

Program::Program()
{
}

Program::~Program()
{
    this->destroy();
}

void Program::create(std::string vertex, std::string fragment)
{
    this->m_program = LoadShaders(vertex.c_str(), fragment.c_str());
}

void Program::destroy()
{
    glDeleteProgram(this->m_program);
}

void Program::use()
{
    glUseProgram(this->m_program);
}

GLuint Program::getId()
{
    return this->m_program;
}
