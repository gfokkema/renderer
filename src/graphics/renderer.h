#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include "gl/gl.h"
#include "util/camera.h"

namespace graphics {

class Renderer;
class Renderable3D;
class AdvRenderable3D;
class SimpleRenderable3D;

typedef std::shared_ptr<Renderable3D> renderable_ptr;
typedef std::shared_ptr<AdvRenderable3D> adv_renderable_ptr;
typedef std::shared_ptr<SimpleRenderable3D> simple_renderable_ptr;
typedef std::unique_ptr<Renderer> renderer_ptr;

class Renderer
{
public:
    virtual ~Renderer() {};

    virtual void draw(Camera& camera) = 0;
    virtual void submit(std::vector<renderable_ptr>& renderables) = 0;

    virtual void submit(image_buffer_ptr& buffer);

    std::vector<texture_ptr> m_textures;
};

}

#endif /* GRAPHICS_RENDERER_H_ */
