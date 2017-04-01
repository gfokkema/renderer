#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>

#include "gl/context.h"
#include "util/camera.h"
#include "util/input.h"

namespace gl
{

class Window
{
public:
    Window();
    ~Window();

    void close();
    bool should_close();

    util::Camera& camera();
    util::Input& input();

    void activate();
    void update();
private:
    GLFWwindow* p_window;
    util::Camera m_camera;
    util::Input m_input;
};

}

#endif /* __WINDOW_H */
