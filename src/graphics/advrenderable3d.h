#ifndef GRAPHICS_ADVRENDERABLE3D_H_
#define GRAPHICS_ADVRENDERABLE3D_H_

#include "renderable3d.h"
#include "tiny_obj_loader.h"

namespace graphics
{

class AdvRenderable3D : public Renderable3D
{
public:
    AdvRenderable3D(tinyobj::shape_t& shape, glm::vec3 pos = glm::vec3(0));;
    virtual ~AdvRenderable3D();

    std::vector<gl::VertexData>& data();
    std::vector<unsigned>& index();
private:
    std::vector<gl::VertexData> m_data;
    std::vector<unsigned> m_index;
};

}

#endif /* GRAPHICS_ADVRENDERABLE3D_H_ */
