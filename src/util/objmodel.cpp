#include "objmodel.h"

#include "tiny_obj_loader.h"

ObjModel::ObjModel ()
{
}

ObjModel::~ObjModel ()
{
}

Status ObjModel::load()
{
    std::string err;

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Load our model
    if (!tinyobj::LoadObj(shapes, materials, err, "../altair.obj", "../"))
    {
        std::cerr << "Failed to load obj: " << err << std::endl;
        return STATUS_ERR;
    }
    std::cout << "# shapes   : " << shapes.size() << std::endl;
    std::cout << "# materials: " << materials.size() << std::endl;

    for (auto i = 0; i < shapes.size(); i++)
    {
        std::cout << i << " name: " << shapes[i].name << std::endl;
        std::cout << "  size: " << shapes[i].mesh.positions.size() << std::endl;
    }

    return STATUS_OK;
}
