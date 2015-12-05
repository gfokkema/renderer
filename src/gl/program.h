#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "common.h"

class Program {
public:
    Program();
    ~Program();

    void create();
    void destroy();

    Status load(std::string, std::string);
    void use();

    GLuint getId();
private:
    GLuint m_program;
};

#endif /* __PROGRAM_H */
