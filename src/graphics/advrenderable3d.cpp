#include <graphics/advrenderable3d.h>

graphics::AdvRenderable3D::AdvRenderable3D(tinyobj::shape_t& shape, glm::vec3 pos)
: Renderable3D(pos, shape.mesh.material_ids.front())
{
    auto& vec = shape.mesh.positions;
    auto& tex = shape.mesh.texcoords;
    for (auto i = 0; i * 3 < vec.size(); i++)
    {
        m_data.push_back(gl::VertexData {
            glm::vec3(vec[i * 3 + 0], vec[i * 3 + 1], vec[i * 3 + 2]),
            glm::vec2(tex[i * 2 + 0], tex[i * 2 + 1]),
            this->texid(),
        });
    }

    m_index.insert(m_index.begin(), shape.mesh.indices.begin(), shape.mesh.indices.end());
}

graphics::AdvRenderable3D::~AdvRenderable3D()
{
}

std::vector<graphics::gl::VertexData>&
graphics::AdvRenderable3D::data()
{
    return this->m_data;
}

std::vector<unsigned>&
graphics::AdvRenderable3D::index()
{
    return this->m_index;
}
