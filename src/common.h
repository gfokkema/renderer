#ifndef __COMMON_H__
#define __COMMON_H__

#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <glm/glm.hpp>

#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

class BaseException : public std::exception
{
public:
    BaseException(std::string msg)
    : msg(msg)
    {
    };
    virtual const char* what() const throw()
    {
        return this->msg.c_str();
    };
private:
    std::string msg;
};

inline void check(std::string msg)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw BaseException(msg);
};

#endif /* __COMMON_H__ */
