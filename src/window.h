#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>

#include "gl/context.h"
#include "camera.h"

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
    Camera m_camera;
};

#endif /* __WINDOW_H */
