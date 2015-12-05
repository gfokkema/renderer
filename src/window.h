#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gl/context.h"

class Window {
public:
    Window();
    ~Window();

    Status create();
    void destroy();

    void draw(Context& ctx);
    void update();

    Status shouldClose();
private:
    GLFWwindow* p_window;

    glm::mat4 m_mvp;
};

#endif /* __WINDOW_H */
