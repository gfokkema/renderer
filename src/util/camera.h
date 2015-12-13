#ifndef CAMERA_H_
#define CAMERA_H_

#include "common.h"

namespace util
{

class Camera
{
public:
    Camera(float aspect_ratio);
    ~Camera();

    glm::mat4 matrix();

    void left();
    void right();
    void forward();
    void backward();
private:
    glm::vec3 m_pos;
    glm::vec3 m_dir;
    glm::vec3 m_up;

    glm::mat4 m_projection;
    glm::mat4 m_view;
};

}

#endif /* CAMERA_H_ */
