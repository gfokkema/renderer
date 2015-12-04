#include "program.h"

#include <iostream>
#include <vector>

#include "shader.h"

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

Status Program::load(std::string vertex, std::string fragment)
{
    int result = 0;
    int log_size = 0;

    Shader vertexshader(GL_VERTEX_SHADER);
    vertexshader.create();
    vertexshader.load(vertex);
    vertexshader.compile();

    Shader fragmentshader(GL_FRAGMENT_SHADER);
    fragmentshader.create();
    fragmentshader.load(fragment);
    fragmentshader.compile();

    // Link the program
    std::cout << "Linking program." << std::endl;
    glAttachShader(this->m_program, vertexshader.getId());
    glAttachShader(this->m_program, fragmentshader.getId());
    glLinkProgram(this->m_program);

    // Check the program
    glGetProgramiv(this->m_program, GL_LINK_STATUS, &result);
    glGetProgramiv(this->m_program, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 1) {
        std::vector<char> program_log(log_size + 1);
        glGetProgramInfoLog(this->m_program, log_size, NULL, &program_log.front());
        std::cout << program_log[0] << std::endl;
    }
    glDetachShader(this->m_program, vertexshader.getId());
    glDetachShader(this->m_program, fragmentshader.getId());

    vertexshader.destroy();
    fragmentshader.destroy();

    return result == GL_TRUE ? STATUS_OK : STATUS_ERR;
}

void Program::use()
{
    glUseProgram(this->m_program);
}

GLuint Program::getId()
{
    return this->m_program;
}
