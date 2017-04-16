#include "objmodel.h"

util::ObjModel::ObjModel(std::string base_path, std::string rel_path)
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(shapes, materials, err,
                          (base_path + rel_path).c_str(),
                          base_path.c_str()))
        throw BaseException("Failed to load obj: " + err);

    for (auto shape : shapes)
    {
        this->m_shapes.push_back(shape);

        fmt::print(" shape name: {}\n", shape.name);
        fmt::print(" shape size: {}\n", shape.mesh.positions.size());
    }
    fmt::print("# shapes   : {}\n", m_shapes.size());

    for (auto material : materials)
    {
        Material mat(material, base_path);
        this->m_materials.push_back(mat);
    }
    fmt::print("# materials: {}\n", m_materials.size());
}

util::ObjModel::~ObjModel()
{
}
