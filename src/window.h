#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>

#include "gl/context.h"
#include "util/camera.h"

namespace gl
{

class Window
{
public:
    Window();
    ~Window();

    Status create();
    void destroy();

    util::Camera& camera();
    void refresh();
    Status should_close();
    void update();

private:
    GLFWwindow* p_window;
    util::Camera m_camera;
};

}

#endif /* __WINDOW_H */
