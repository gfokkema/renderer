#include "window.h"

#include <unistd.h>

void
key_callback(GLFWwindow* gl_window, int key, int scancode, int action, int mods)
{
    static std::map<int, void (util::Input::*)(int, int, int)> cbmap
    {
        std::make_pair(GLFW_PRESS, &util::Input::key_pressed),
        std::make_pair(GLFW_REPEAT, &util::Input::key_pressed),
        std::make_pair(GLFW_RELEASE, &util::Input::key_released),
    };
    graphics::Window* window = (graphics::Window*)glfwGetWindowUserPointer(gl_window);

    (window->input().*cbmap[action])(key, scancode, mods);
}

void
mouse_callback(GLFWwindow* gl_window, int button, int action, int mods)
{
    static std::map<bool, void (util::Input::*)(int, int)> cbmap
    {
        std::make_pair(GLFW_PRESS,   &util::Input::mouse_pressed),
        std::make_pair(GLFW_RELEASE, &util::Input::mouse_released),
    };
    graphics::Window* window = (graphics::Window*)glfwGetWindowUserPointer(gl_window);

    (window->input().*cbmap[action])(button, mods);
}

graphics::Window::Window()
{
    if (!glfwInit())
        throw BaseException("Failed to initialize GLFW");

    glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                 // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    this->p_window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", NULL, NULL);
    if (!this->p_window)
    {
        glfwTerminate();
        throw BaseException("Failed to open GLFW window.");
    }

    glfwSetWindowUserPointer(this->p_window, this);
    glfwSetInputMode(this->p_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetTime(0.0);

    glfwSetKeyCallback(this->p_window, &key_callback);
    glfwSetMouseButtonCallback(this->p_window, &mouse_callback);
    // glfwSetWindowSizeCallback?
}

graphics::Window::~Window()
{
    glfwTerminate();
}

void
graphics::Window::close()
{
    glfwSetWindowShouldClose(this->p_window, true);
}

bool
graphics::Window::should_close()
{
    return glfwWindowShouldClose(this->p_window);
}

util::Input&
graphics::Window::input()
{
    return this->m_input;
}

void
graphics::Window::activate()
{
    glfwMakeContextCurrent(this->p_window);
}

void
graphics::Window::update()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        fmt::print("GL error: {}\n", error);

    glfwPollEvents();
    glfwSwapBuffers(this->p_window);
}
