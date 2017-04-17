#include "renderable3d.h"

graphics::Renderable3D::Renderable3D(glm::vec3 pos, unsigned short texid)
: m_pos(pos), m_texid(texid)
{
}

graphics::Renderable3D::~Renderable3D()
{
}

unsigned short
graphics::Renderable3D::texid()
{
    return this->m_texid;
}
