#include "window.h"

#include <iostream>
#include <unistd.h>

#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 640
#define HEIGHT 480

// An array of 3 vectors which represents 3 vertices
const std::vector<float> vertex_buffer_data({
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
});

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
    double middle_x = WIDTH/2.0;
    double middle_y = HEIGHT/2.0;

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
{
}

Window::~Window()
{
    this->destroy();
}

int Window::create()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

    // Open a window and create its OpenGL context
    this->p_window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", NULL, NULL);
    if (!this->p_window)
    {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(this->p_window);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glfwSetInputMode(this->p_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetKeyCallback(this->p_window, &key_callback);
    glfwSetWindowFocusCallback(this->p_window, &focus_callback);

    return 0;
}

void Window::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Belongs to some scene class or something like it.
    this->program.create("../src/shaders/shader.vertex.c", "../src/shaders/shader.fragment.c");
    this->vao.create();
    this->vao.bind();
    this->vbo.create();
    this->vbo.bind();
    this->vbo.setdata(GL_ARRAY_BUFFER, vertex_buffer_data, GL_STATIC_DRAW);

    // Belongs to some camera class or something like it.
    this->matrix = glGetUniformLocation(this->program.getId(), "mvp");
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 m_projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 m_view = glm::lookAt(
       glm::vec3(0,0,-2), // Camera is at (0,0,-2), in World Space
       glm::vec3(0,0,0),  // and looks at the origin
       glm::vec3(0,1,0)   // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 m_model = glm::mat4(1.0f);

    m_mvp = m_projection * m_view * m_model; // Remember, matrix multiplication is the other way around
}
    
void Window::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->program.use();

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &m_mvp[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    vbo.bind();
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

void Window::destroy()
{
    this->program.destroy();
    this->vbo.destroy();
    this->vao.destroy();

    glfwTerminate();
}

int Window::shouldClose()
{
    return glfwWindowShouldClose(this->p_window);
}

void Window::update()
{
    glfwSwapBuffers(this->p_window);
    glfwPollEvents();
}
