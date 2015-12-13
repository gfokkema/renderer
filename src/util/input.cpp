#include "input.h"

#include <GLFW/glfw3.h>

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

util::Input::Input()
{
}

util::Input::~Input()
{
}

void
util::Input::key_pressed(int key, int scancode, int modifiers)
{
    this->keystate[key] = true;
}

void
util::Input::key_released(int key, int scancode, int modifiers)
{
    this->keystate[key] = false;
}

void
util::Input::mouse_pressed(int button, int modifiers)
{
}

void
util::Input::mouse_released(int button, int modifiers)
{
}

bool
util::Input::operator[](int key)
{
    return this->keystate[key];
}
