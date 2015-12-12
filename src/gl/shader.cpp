#include "shader.h"

gl::Shader::Shader (GLenum type)
: m_shader(0), m_type(type)
{
}

gl::Shader::~Shader ()
{
    this->destroy();
}

void
gl::Shader::create()
{
    this->m_shader = glCreateShader(this->m_type);
}

void
gl::Shader::destroy()
{
    glDeleteShader(this->m_shader);
}

Status
gl::Shader::load(std::string path)
{
    this->create();

    if (this->read(path) != STATUS_OK)
        return STATUS_ERR;

    if (this->compile() != STATUS_OK)
        return STATUS_ERR;

    return STATUS_OK;
}


Status
gl::Shader::read(std::string path)
{
    // Read the Vertex Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(path, std::ios::in);
    if(!shaderStream.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return STATUS_ERR;
    }

    std::string line = "";
    while(getline(shaderStream, line))
    {
        shaderCode += "\n" + line;
    }
    shaderStream.close();

    char const* shaderPointer = shaderCode.c_str();
    glShaderSource(this->m_shader, 1, &shaderPointer, NULL);

    return STATUS_OK;
}

Status
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

    return result == GL_TRUE ? STATUS_OK : STATUS_ERR;
}

GLuint
gl::Shader::getId()
{
    return this->m_shader;
}
