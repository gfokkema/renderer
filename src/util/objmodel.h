#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include "common.h"
#include "material.h"
#include "tiny_obj_loader.h"

namespace util
{

class ObjModel {
public:
    ObjModel(std::string, std::string);
    ~ObjModel();

    std::vector<tinyobj::shape_t> m_shapes;
    std::vector<Material> m_materials;
};

}

#endif /* OBJMODEL_H_ */
