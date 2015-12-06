#include "window.h"

#include <unistd.h>

#define WIDTH 640
#define HEIGHT 480

/* Time independent keyboard function */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, 1);
        break;
    }
}

/* Focus callback function */
void focus_callback(GLFWwindow* window, int focused)
{
    if (focused) {
        double middle_x = WIDTH / 2.0;
        double middle_y = HEIGHT / 2.0;
        glfwSetCursorPos(window, middle_x, middle_y);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void handle_mouse(GLFWwindow* window)
{
    double middle_x = WIDTH / 2.0;
    double middle_y = HEIGHT / 2.0;

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (x < WIDTH && y < HEIGHT)
    {
        double dx = x - middle_x;
        double dy = y - middle_y;
        if (dx == 0.f && dy == 0.f) return;
    }
    glfwSetCursorPos(window, middle_x, middle_y);
}

Window::Window()
: p_window(nullptr), m_camera((float)WIDTH / (float)HEIGHT)
{
}

Window::~Window()
{
    this->destroy();
}

Status Window::create()
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

    glfwMakeContextCurrent(this->p_window);
    glfwSetInputMode(this->p_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(this->p_window, &key_callback);
    glfwSetWindowFocusCallback(this->p_window, &focus_callback);

    glfwSetTime(0.0);

    return STATUS_OK;
}

void Window::destroy()
{
    glfwTerminate();
}

void Window::draw(Context& ctx, ObjModel& model)
{
    ctx.draw(this->m_camera, model);
    glfwSwapBuffers(this->p_window);
}

Status Window::shouldClose()
{
    if (glfwWindowShouldClose(this->p_window))
        return STATUS_OK;
    else
        return STATUS_ERR;
}

void Window::update()
{
    glfwPollEvents();
}
