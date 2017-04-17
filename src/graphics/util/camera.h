#ifndef CAMERA_H_
#define CAMERA_H_

#include "common.h"

#include "msg/channel.h"

class Movement;

namespace graphics {

class Camera : public Sink<Movement>
{
public:
    Camera(float aspect_ratio);
    ~Camera();

    glm::mat4 matrix();

    void apply(const Movement *);
private:
    glm::vec3 m_pos;
    glm::vec3 m_dir;
    glm::vec3 m_up;

    glm::mat4 m_projection;
    glm::mat4 m_view;
};

}

#endif /* CAMERA_H_ */
