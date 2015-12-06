#include "objmodel.h"

ObjModel::ObjModel ()
{
}

ObjModel::~ObjModel ()
{
}

Status ObjModel::load()
{
    std::string err;

    // Load our model
    if (!tinyobj::LoadObj(this->m_shapes, this->m_materials, err, "../cubes.obj", "../"))
    {
        std::cerr << "Failed to load obj: " << err << std::endl;
        return STATUS_ERR;
    }
    std::cout << "# shapes   : " << m_shapes.size() << std::endl;
    std::cout << "# materials: " << m_materials.size() << std::endl;

    for (auto i = 0; i < m_shapes.size(); i++)
    {
        std::cout << i << " name: " << m_shapes[i].name << std::endl;
        std::cout << "  size: " << m_shapes[i].mesh.positions.size() << std::endl;
    }

    return STATUS_OK;
}
