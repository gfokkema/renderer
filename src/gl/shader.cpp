#include "shader.h"
#include "util/file.h"

gl::Shader::Shader(GLenum type)
: m_type(type)
{
    this->getId() = glCreateShader(type);
    check("Error creating shader.");
}

gl::Shader::~Shader()
{
    std::cout << "Destroying shader." << std::endl;
    glDeleteShader(this->getId());
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

    glShaderSource(this->getId(), 1, &source, NULL);
    check("Failed to upload file: " + path);
}

void
gl::Shader::compile() const
{
    int result = 0;
    int log_size = 0;

    std::cout << "Compiling shader." << std::endl;
    glCompileShader(this->getId());
    glGetShaderiv(this->getId(), GL_COMPILE_STATUS, &result);
    glGetShaderiv(this->getId(), GL_INFO_LOG_LENGTH, &log_size);

    if (log_size > 1) {
        std::vector<char> shader_log(log_size + 1);

        glGetShaderInfoLog(this->getId(), log_size, NULL, &shader_log.front());
        printf("Shader log: %s\n", &shader_log.front());
    }

    if (result == GL_FALSE)
        throw BaseException("Failed to compile shader.");
}
