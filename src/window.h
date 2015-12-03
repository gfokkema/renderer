#ifndef __WINDOW_H
#define __WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gl/program.h"
#include "gl/vertexarray.h"
#include "gl/vertexbuffer.h"

class Window {
public:
    Window();
    ~Window();
    int create();
    void destroy();
    void init();
    void draw();
    void update();
    int shouldClose();
private:
    GLFWwindow* p_window;
    Program program;
    VertexArray vao;
    VertexBuffer vbo;
    GLuint matrix;
    glm::mat4 m_mvp;
};

#endif /* __WINDOW_H */
