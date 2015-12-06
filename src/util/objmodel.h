#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include "common.h"

#include "tiny_obj_loader.h"

class ObjModel {
public:
    ObjModel ();
    ~ObjModel ();

    Status load();
    std::vector<tinyobj::shape_t> m_shapes;
    std::vector<tinyobj::material_t> m_materials;
};

#endif /* OBJMODEL_H_ */
