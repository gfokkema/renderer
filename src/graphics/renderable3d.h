#ifndef GRAPHICS_RENDERABLE3D_H_
#define GRAPHICS_RENDERABLE3D_H_

#include "gl/gl.h"

namespace graphics
{

class Renderable3D
{
public:
    Renderable3D(glm::vec3 pos = glm::vec3(0), unsigned short texid = 0);
    virtual ~Renderable3D();

    unsigned short texid();
private:
    glm::vec3 m_pos;
    unsigned short m_texid;
};

}

#endif /* GRAPHICS_RENDERABLE3D_H_ */
