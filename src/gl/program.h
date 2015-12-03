#ifndef __PROGRAM_H
#define __PROGRAM_H

#include <GL/glew.h>

#include <string>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

class Program {
public:
    Program();
    ~Program();

    void create(std::string, std::string);
    void destroy();
    void use();

    GLuint getId();
private:
    GLuint m_program;
};

#endif /* __PROGRAM_H */
