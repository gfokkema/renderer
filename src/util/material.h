#ifndef UTIL_MATERIAL_H_
#define UTIL_MATERIAL_H_

#include "common.h"
#include "gl/texture.h"

#include "tiny_obj_loader.h"

namespace util
{

enum IMAGE_MAP
{
    AMBIENT,
    DIFFUSE,
    SPECULAR,
    SPECULAR_HIGH,
    BUMP,
    DISPLACEMENT,
    ALPHA,
};

typedef std::pair<IMAGE_MAP, std::string> image_path_entry;

class Material {
public:
    Material(tinyobj::material_t, std::string = "");
    ~Material();

    void load();
    std::shared_ptr<gl::image_buffer> get_buffer(IMAGE_MAP) const;
private:
    tinyobj::material_t m_material;

    std::map<IMAGE_MAP, std::shared_ptr<gl::image_buffer>> m_buffers;
};

}

#endif /* UTIL_MATERIAL_H_ */
