#ifndef GLRENDERER_RENDERER_H_
#define GLRENDERER_RENDERER_H_

#include "util/camera.h"
#include "renderable3d.h"

namespace glrenderer {

typedef std::unique_ptr<gl::Texture> texture;
typedef std::shared_ptr<Renderable3D> renderable;

class Renderer
{
public:
    Renderer(std::vector<texture> textures) : m_textures(std::move(textures)) {};
    virtual ~Renderer() {};

    virtual void draw(util::Camera& camera) = 0;
    virtual void submit(std::vector<renderable>& renderables) = 0;
private:
    std::vector<texture> m_textures;
};

}

#endif /* GLRENDERER_RENDERER_H_ */
