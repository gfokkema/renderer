#ifndef UTIL_INPUT_H_
#define UTIL_INPUT_H_

#include "common.h"

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

    std::map<int, bool> getkeystate();
private:
    std::map<int, bool> keystate;
    bool lmb = false, rmb = false;
};

}

#endif /* UTIL_INPUT_H_ */
