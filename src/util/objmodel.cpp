#include "objmodel.h"

#include "material.h"

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

        std::cout << " shape name: " << shape.name << std::endl;
        std::cout << " shape size: " << shape.mesh.positions.size() << std::endl;
    }
    std::cout << "# shapes   : " << m_shapes.size() << std::endl;

    for (auto material : materials)
    {
        Material mat(material, base_path);
        if (mat.load() != STATUS_OK)
            throw BaseException("Failed to load: " + material.name);

        this->m_materials.push_back(mat);
    }
    std::cout << "# materials: " << m_materials.size() << std::endl;
}

util::ObjModel::~ObjModel()
{
}
