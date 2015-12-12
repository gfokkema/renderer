#include "objmodel.h"

#include "material.h"

util::ObjModel::ObjModel()
{
}

util::ObjModel::~ObjModel()
{
}

Status
util::ObjModel::load(std::string base_path, std::string rel_path)
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(shapes, materials, err,
                          (base_path + rel_path).c_str(), base_path.c_str()))
    {
        std::cerr << "Failed to load obj: " << err << std::endl;
        return STATUS_ERR;
    }

    for (auto shape : shapes)
    {
        this->load(shape);
    }
    for (auto material : materials)
    {
        this->load(material, base_path);
    }

    std::cout << "# shapes   : " << m_shapes.size() << std::endl;
    std::cout << "# materials: " << m_materials.size() << std::endl;

    return STATUS_OK;
}

Status
util::ObjModel::load(tinyobj::shape_t shape)
{
    this->m_shapes.push_back(shape);

    std::cout << " shape name: " << shape.name << std::endl;
    std::cout << " shape size: " << shape.mesh.positions.size() << std::endl;
}

Status
util::ObjModel::load(tinyobj::material_t material, std::string base_path)
{
    Material mat(material, base_path);

    if (mat.load() != STATUS_OK)
    {
        std::cout << "Failed to load " << material.name << "." << std::endl;
        return STATUS_ERR;
    }

    this->m_materials.push_back(mat);

    return STATUS_OK;
}
