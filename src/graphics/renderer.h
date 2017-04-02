#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "camera.h"
#include "renderable3d.h"

namespace graphics {

typedef std::unique_ptr<gl::Texture> texture;
typedef std::shared_ptr<Renderable3D> renderable;

class Renderer
{
public:
    Renderer(std::vector<texture> textures) : m_textures(std::move(textures)) {};
    virtual ~Renderer() {};

    virtual void draw(Camera& camera) = 0;
    virtual void submit(std::vector<renderable>& renderables) = 0;
private:
    std::vector<texture> m_textures;
};

}

#endif /* GRAPHICS_RENDERER_H_ */
