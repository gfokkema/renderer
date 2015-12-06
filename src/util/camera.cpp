#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera (float aspect_ratio)
{
    this->m_projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);
    this->m_view = glm::lookAt(
       glm::vec3(0,3,-10), // Camera is at (0,0,-2), in World Space
       glm::vec3(0,0,0),  // and looks at the origin
       glm::vec3(0,1,0)   // Head is up (set to 0,-1,0 to look upside-down)
    );
}

Camera::~Camera ()
{
}

glm::mat4 Camera::matrix()
{
    return m_projection * m_view;
}
