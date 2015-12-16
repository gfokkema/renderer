#include "camera.h"

#include "msg/movement.h"

#include <glm/gtc/matrix_transform.hpp>

util::Camera::Camera (float aspect_ratio)
: m_pos(0, 2, 5), m_dir(0, 0, -1), m_up(0, 1, 0)
{
    this->m_projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
}

util::Camera::~Camera ()
{
}

glm::mat4
util::Camera::matrix()
{
    this->m_view = glm::lookAt(
       this->m_pos,
       this->m_pos + this->m_dir,
       this->m_up
    );
    return m_projection * m_view;
}

void
util::Camera::move(glm::vec3 movement)
{
    m_pos += movement;
}

void
util::Camera::send(const Movement * movement)
{
    movement->apply(this);
}
