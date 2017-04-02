#include "shader.h"
#include "util/file.h"

gl::Shader::Shader (GLenum type)
: m_type(type)
{
    this->m_shader = glCreateShader(type);
    check("Error creating shader.");
}

gl::Shader::~Shader ()
{
    glDeleteShader(this->m_shader);
    check("Error deleting shader.");
}

void
gl::Shader::load(std::string path) const
{
    this->read(path);
    this->compile();
}


void
gl::Shader::read(std::string path) const
{
    std::string text = util::File(path).read();
    char const* source = text.c_str();

    glShaderSource(this->m_shader, 1, &source, NULL);
    check("Failed to upload file: " + path);
}

void
gl::Shader::compile() const
{
    int result = 0;
    int log_size = 0;

    std::cout << "Compiling shader." << std::endl;
    glCompileShader(this->m_shader);
    glGetShaderiv(this->m_shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(this->m_shader, GL_INFO_LOG_LENGTH, &log_size);

    if (log_size > 1) {
        std::vector<char> shader_log(log_size + 1);

        glGetShaderInfoLog(this->m_shader, log_size, NULL, &shader_log.front());
        printf("Shader log: %s\n", &shader_log.front());
    }

    if (result == GL_FALSE)
        throw BaseException("Failed to compile shader.");
}

GLuint
gl::Shader::getId() const
{
    return this->m_shader;
}
