#include "material.h"

#include <FreeImage.h>

std::vector<util::image_path_entry>
image_paths(tinyobj::material_t material)
{
    using namespace util;

    return std::vector<image_path_entry>({
        image_path_entry(AMBIENT,       material.ambient_texname),
        image_path_entry(DIFFUSE,       material.diffuse_texname),
        image_path_entry(SPECULAR,      material.specular_texname),
        image_path_entry(SPECULAR_HIGH, material.specular_highlight_texname),
        image_path_entry(BUMP,          material.bump_texname),
        image_path_entry(DISPLACEMENT,  material.displacement_texname),
        image_path_entry(ALPHA,         material.alpha_texname),
    });
}

std::shared_ptr<gl::image_buffer>
load_img(std::string path)
{
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str());
    FIBITMAP* img = FreeImage_Load(format, path.c_str());
    if (!img || format == FIF_UNKNOWN)
        throw BaseException("Error loading material file: " + path);

    std::shared_ptr<gl::image_buffer> buf(new gl::image_buffer);
    buf->w = FreeImage_GetWidth(img);
    buf->h = FreeImage_GetHeight(img);
    buf->data = std::vector<unsigned char>(buf->size());

    FreeImage_ConvertToRawBits(buf->data.data(), img, buf->w * 3, 24, 0, 0, 0);
    FreeImage_Unload(img);

    return buf;
}

util::Material::Material(tinyobj::material_t material,
                         std::string base_path)
: m_material(material)
{
    std::cout << " mat name: " << this->m_material.name << std::endl;

    for (auto image_path : image_paths(this->m_material))
    {
        if (image_path.second.size() == 0) continue;

        std::string path = base_path + image_path.second;
        this->m_buffers[image_path.first] = load_img(path);

        std::cout << " mat path: " << path << std::endl;
    }
}

util::Material::~Material()
{
}

std::shared_ptr<gl::image_buffer>
util::Material::get_buffer(IMAGE_MAP tex) const
{
    return this->m_buffers.at(tex);
}
