#include "shader.h"

graphics::gl::Shader::Shader(GLenum type)
: m_type(type)
{
    this->getId() = glCreateShader(type);
    check("Error creating shader.");
}

graphics::gl::Shader::~Shader()
{
    fmt::print("Destroying shader.\n");
    glDeleteShader(this->getId());
    check("Error deleting shader.");
}

void
graphics::gl::Shader::load(std::string text) const
{
    this->read(text);
    this->compile();
}


void
graphics::gl::Shader::read(std::string text) const
{
    char const* source = text.c_str();

    glShaderSource(this->getId(), 1, &source, NULL);
    check("Failed to upload file: " + text);
}

void
graphics::gl::Shader::compile() const
{
    int result = 0;
    int log_size = 0;

    fmt::print("Compiling shader.\n");
    glCompileShader(this->getId());
    glGetShaderiv(this->getId(), GL_COMPILE_STATUS, &result);
    glGetShaderiv(this->getId(), GL_INFO_LOG_LENGTH, &log_size);

    if (log_size > 1) {
        std::vector<char> shader_log(log_size + 1);

        glGetShaderInfoLog(this->getId(), log_size, NULL, &shader_log.front());
        fmt::print("Shader log: {}\n", &shader_log.front());
    }

    if (result == GL_FALSE)
        throw BaseException("Failed to compile shader.");
}
