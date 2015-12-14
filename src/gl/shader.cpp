#include "shader.h"

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
gl::Shader::load(std::string path)
{
    this->read(path);
    this->compile();
}


void
gl::Shader::read(std::string path)
{
    // Read the Vertex Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(path, std::ios::in);
    if(!shaderStream.is_open())
        throw BaseException("Failed to open file: " + path);

    std::string line = "";
    while(getline(shaderStream, line))
    {
        shaderCode += "\n" + line;
    }
    shaderStream.close();

    char const* shaderPointer = shaderCode.c_str();
    glShaderSource(this->m_shader, 1, &shaderPointer, NULL);

    check("Failed to upload file: " + path);
}

void
gl::Shader::compile()
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
gl::Shader::getId()
{
    return this->m_shader;
}
