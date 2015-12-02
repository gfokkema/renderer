#include <iostream>
#include <unistd.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#define WIDTH 640
#define HEIGHT 480

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

namespace {
GLFWwindow* window;

/**
 * Time independent keyboard function
 */
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, 1);
        break;
    }
}

/**
 * Focus callback function
 */
void focus_callback(GLFWwindow * window, int focused) {
//    if (focused) {
//        double middle_x = WIDTH/2.0;
//        double middle_y = HEIGHT/2.0;
//        glfwSetCursorPos(window, middle_x, middle_y);
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    }
}

void handle_mouse() {
    double middle_x = WIDTH/2.0;
    double middle_y = HEIGHT/2.0;

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (x < WIDTH && y < HEIGHT) {
        double dx = x - middle_x;
        double dy = y - middle_y;
        if (dx == 0.f && dy == 0.f) return;

//        cam.lookAt(x, HEIGHT - y);
    }
    glfwSetCursorPos(window, middle_x, middle_y);
}

/**
 * Time dependent keyboard function
 */
void handle_keyboard(float dt) {
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) cam.strafe(-1.f, dt);
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) cam.strafe(1.f, dt);
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) cam.move(1.f, dt);
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) cam.move(-1.f, dt);
}

void handle_input(float dt) {
    handle_keyboard(dt);
//    handle_mouse();
}
}

 // An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main(int argc, char* argv[]) {
    GLuint program;
    GLuint vertexarray;
    GLuint vertexbuffer;
    GLuint matrix;

    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Raytracer", NULL, NULL);
    if( window == NULL ){
        std::cerr << "Failed to open GLFW window.\n" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the keyboard callback for time independent keyboard handling
    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowFocusCallback(window, &focus_callback);

    // Create and compile our GLSL program from the shaders
    program = LoadShaders( "../src/shader.vertex.c", "../src/shader.fragment.c");

    // Create and bind a VAO
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);

    // This will identify our vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    // Give our vertices to OpenGL.
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Get a handle for our "MVP" uniform
    matrix = glGetUniformLocation(program, "mvp");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 m_projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 m_view = glm::lookAt(
       glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
       glm::vec3(0,0,0), // and looks at the origin
       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 m_model = glm::mat4(1.0f);
    glm::mat4 m_mvp = m_projection * m_view * m_model; // Remember, matrix multiplication is the other way around

    // Set the timer to zero
    glfwSetTime(0.0);
    double prev = 0;
    unsigned frames = 0;
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(program);

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        glUniformMatrix4fv(matrix, 1, GL_FALSE, &m_mvp[0][0]);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double cur = glfwGetTime();
        handle_input(cur - prev);

        //std::cout << "FPS: " << ++frames / cur << "\r";
        //std::flush(std::cout);
        prev = cur;
    } while(!glfwWindowShouldClose(window));

    std::cout << std::endl;

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexarray);
    glDeleteProgram(program);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}
