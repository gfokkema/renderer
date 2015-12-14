#include "window.h"

#include <unistd.h>

#define WIDTH 1920
#define HEIGHT 1080

gl::Window::Window(util::Input& input)
: m_camera((float)WIDTH / (float)HEIGHT)
{
    if (!glfwInit())
        throw BaseException("Failed to initialize GLFW");

    glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    this->p_window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", NULL, NULL);
    if (!this->p_window)
    {
        glfwTerminate();
        throw BaseException("Failed to open GLFW window.");
    }

    glfwSetWindowUserPointer(this->p_window, &input);
    glfwMakeContextCurrent(this->p_window);
    glfwSetInputMode(this->p_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(this->p_window, &key_callback);
    glfwSetMouseButtonCallback(this->p_window, &mouse_callback);

    glfwSetTime(0.0);
}

gl::Window::~Window()
{
    glfwTerminate();
}

void
gl::Window::close()
{
    glfwSetWindowShouldClose(this->p_window, 1);
}

bool
gl::Window::should_close()
{
    return glfwWindowShouldClose(this->p_window) != 0;
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
