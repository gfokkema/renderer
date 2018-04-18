#ifndef __WINDOW_H
#define __WINDOW_H

#include "common.h"

#include <GLFW/glfw3.h>
#include <graphics/util/camera.h>

#include "util/input.h"
#include "simplerenderer3d.h"

namespace graphics {

class Window
{
public:
    Window();
    ~Window();

    void close();
    bool should_close();

    util::Input& input();

    void activate();
    void update();
private:
    GLFWwindow* p_window;
    util::Input m_input;
};

}

#endif /* __WINDOW_H */
