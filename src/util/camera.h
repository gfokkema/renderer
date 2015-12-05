#ifndef CAMERA_H_
#define CAMERA_H_

#include "common.h"

class Camera {
public:
    Camera(float aspect_ratio);
    ~Camera();

    glm::mat4 matrix();
private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif /* CAMERA_H_ */
