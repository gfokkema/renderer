#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>

#include "util/input.h"
#include "camera.h"
#include "renderer3d.h"

namespace graphics {

class Window
{
public:
    Window();
    ~Window();

    void close();
    bool should_close();

    Camera& camera();
    util::Input& input();

    void activate();
    void update();
private:
    GLFWwindow* p_window;
    Camera m_camera;
    util::Input m_input;
};

}

#endif /* __WINDOW_H */
