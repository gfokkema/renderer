#include "renderable3d.h"

graphics::Renderable3D::Renderable3D(glm::vec3 pos, short texid)
: m_pos(pos), m_texid(texid)
{
}

graphics::Renderable3D::~Renderable3D()
{
}

short
graphics::Renderable3D::texid()
{
    return this->m_texid;
}
