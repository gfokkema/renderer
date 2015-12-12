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

Status
load_img(gl::image_buffer& buf, std::string path)
{
    FREE_IMAGE_FORMAT format;
    FIBITMAP* img;

    format = FreeImage_GetFileType(path.c_str());
    if (format == FIF_UNKNOWN)
        return STATUS_ERR;

    img = FreeImage_Load(format, path.c_str());
    if (!img)
        return STATUS_ERR;

    buf.w = FreeImage_GetWidth(img);
    buf.h = FreeImage_GetHeight(img);

    unsigned size = buf.w * buf.h * 3;
    buf.data = std::vector<unsigned char>(size);
    FreeImage_ConvertToRawBits(buf.data.data(), img, buf.w * 3, 24, 0, 0, 0);
    FreeImage_Unload(img);

    return STATUS_OK;
}

util::Material::Material(tinyobj::material_t material, std::string base_path)
: m_material(material), m_base_path(base_path)
{
}

util::Material::~Material()
{
}

Status
util::Material::load()
{
    std::cout << " mat name: " << this->m_material.name << std::endl;

    for (auto image_path : image_paths(this->m_material))
    {
        if (image_path.second.size() == 0) continue;

        gl::image_buffer buf;
        std::string path = this->m_base_path + image_path.second;

        if (load_img(buf, path) != STATUS_OK)
            return STATUS_ERR;

        this->m_buffers.insert(image_buffer_entry(image_path.first, buf));

        std::cout << " mat path: " << path << std::endl;
        std::cout << " mat size: (" << buf.w << "," << buf.w << std::endl;
    }

    return STATUS_OK;
}

gl::image_buffer
util::Material::get_buffer(IMAGE_MAP tex)
{
    return this->m_buffers[tex];
}
