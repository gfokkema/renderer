#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "msg/movement.h"

graphics::Camera::Camera (float aspect_ratio)
: m_pos(0, 2, 5),
  m_dir(0, 0, -1),
  m_up(0, 1, 0)
{
    this->m_projection = glm::perspective(glm::radians(45.0f),
                                          aspect_ratio, 0.1f, 100.0f);
}

graphics::Camera::~Camera ()
{
}

glm::mat4
graphics::Camera::matrix()
{
    this->m_view = glm::lookAt(
       this->m_pos,
       this->m_pos + this->m_dir,
       this->m_up
    );
    return m_projection * m_view;
}

void
graphics::Camera::apply(const Movement * movement)
{
    m_pos += movement->m_movement;
}
