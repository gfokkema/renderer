#include "movement.h"
#include "util/camera.h"

Movement::Movement(glm::vec3 movement)
: m_movement(movement)
{
}

Movement::~Movement()
{
}

void
Movement::apply(util::Camera* camera) const
{
    camera->move(this->m_movement);
}
