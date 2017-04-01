#include "input.h"

#include <GLFW/glfw3.h>

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
