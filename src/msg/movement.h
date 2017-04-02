#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "common.h"

class Movement
{
public:
    Movement(glm::vec3 movement)
    : m_movement(movement) {};

    ~Movement() {};

    glm::vec3 m_movement;
};

const Movement FORWARD =  Movement(glm::vec3(0, 0, -.1));
const Movement BACKWARD = Movement(glm::vec3(0, 0,  .1));
const Movement LEFT =     Movement(glm::vec3(-.1, 0, 0));
const Movement RIGHT =    Movement(glm::vec3( .1, 0, 0));

#endif /* MOVEMENT_H_ */
