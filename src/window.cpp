#include "window.h"

#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 768

void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static std::map<int, void (util::Input::*)(int, int, int)> cbmap
    {
        std::make_pair(GLFW_PRESS, &util::Input::key_pressed),
        std::make_pair(GLFW_REPEAT, &util::Input::key_pressed),
        std::make_pair(GLFW_RELEASE, &util::Input::key_released),
    };
    util::Input* input = (util::Input*)glfwGetWindowUserPointer(window);

    (input->*cbmap[action])(key, scancode, mods);
}

void
mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    util::Input* input = (util::Input*)glfwGetWindowUserPointer(window);
    auto fn = action == GLFW_PRESS ? &util::Input::mouse_pressed : &util::Input::mouse_released;

    (input->*fn)(button, mods);
}

gl::Window::Window()
: p_window(nullptr), m_camera((float)WIDTH / (float)HEIGHT)
{
}

gl::Window::~Window()
{
    this->destroy();
}

Status
gl::Window::create(util::Input& input)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return STATUS_ERR;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    this->p_window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", NULL, NULL);
    if (!this->p_window)
    {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return STATUS_ERR;
    }

    glfwSetWindowUserPointer(this->p_window, &input);
    glfwMakeContextCurrent(this->p_window);
    glfwSetInputMode(this->p_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(this->p_window, &key_callback);
    glfwSetMouseButtonCallback(this->p_window, &mouse_callback);

    glfwSetTime(0.0);

    return STATUS_OK;
}

void
gl::Window::close()
{
    glfwSetWindowShouldClose(this->p_window, 1);
}

Status
gl::Window::should_close()
{
    return glfwWindowShouldClose(this->p_window) == 0 ? STATUS_ERR : STATUS_OK;
}

void
gl::Window::destroy()
{
    glfwTerminate();
}

util::Camera&
gl::Window::camera()
{
    return m_camera;
}

void
gl::Window::refresh()
{
    glfwSwapBuffers(this->p_window);
}

void
gl::Window::update()
{
    glfwPollEvents();
}
