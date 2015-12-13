#include "input.h"

util::Input::Input()
{
}

util::Input::~Input()
{
}

void
util::Input::key_pressed(int key, int scancode, int modifiers)
{
    this->keystate.insert(std::pair<int, bool>(key, true));
}

void
util::Input::key_released(int key, int scancode, int modifiers)
{
    this->keystate.erase(key);
}

void
util::Input::mouse_pressed(int button, int modifiers)
{
}

void
util::Input::mouse_released(int button, int modifiers)
{
}

std::map<int, bool>
util::Input::getkeystate()
{
    return this->keystate;
}
