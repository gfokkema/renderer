#ifndef __WINDOW_H
#define __WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl/program.h"
#include "gl/vertexarray.h"
#include "gl/vertexbuffer.h"
#include "status.h"

class Window {
public:
    Window();
    ~Window();

    Status create();
    void destroy();

    void init();
    void draw();
    void update();

    Status shouldClose();
private:
    GLFWwindow* p_window;

    Program program;
    VertexArray vao;
    VertexBuffer vbo;

    GLuint matrix;
    glm::mat4 m_mvp;
};

#endif /* __WINDOW_H */
