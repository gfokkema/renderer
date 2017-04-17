#ifndef GRAPHICS_RENDERABLE3D_H_
#define GRAPHICS_RENDERABLE3D_H_

#include "gl/gl.h"

namespace graphics
{

class Renderable3D
{
public:
    Renderable3D(glm::vec3 pos = glm::vec3(0), short texid = 0);
    virtual ~Renderable3D();

    short texid();
private:
    glm::vec3 m_pos;
    short m_texid;
};

}

#endif /* GRAPHICS_RENDERABLE3D_H_ */
