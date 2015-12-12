#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include "common.h"
#include "material.h"
#include "tiny_obj_loader.h"

namespace util
{

class ObjModel {
public:
    ObjModel();
    ~ObjModel();

    Status load(std::string, std::string);
    std::vector<tinyobj::shape_t> m_shapes;
    std::vector<Material> m_materials;

private:
    Status load(tinyobj::shape_t);
    Status load(tinyobj::material_t, std::string);
};

}

#endif /* OBJMODEL_H_ */
