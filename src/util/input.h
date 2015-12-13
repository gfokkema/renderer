#ifndef UTIL_INPUT_H_
#define UTIL_INPUT_H_

#include "common.h"

class GLFWwindow;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);

namespace util
{

class Input
{
public:
    Input();
    ~Input();

    void key_pressed(int, int, int);
    void key_released(int, int, int);

    void mouse_pressed(int, int);
    void mouse_released(int, int);

    bool operator[](int);
private:
    std::map<int, bool> keystate;
    bool lmb = false, rmb = false;
};

}

#endif /* UTIL_INPUT_H_ */
