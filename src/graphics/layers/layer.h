#ifndef GRAPHICS_LAYER_H_
#define GRAPHICS_LAYER_H_

#include "graphics/gl/gl.h"
#include "graphics/renderer.h"
#include "graphics/util/camera.h"

namespace graphics { namespace layers {

class Layer
{
public:
    Layer(renderer_ptr renderer);
    virtual ~Layer();

    void add(image_buffer_ptr buffer);
    void add(renderable_ptr renderable);
    void render();

    Camera& camera();
private:
    std::vector<renderable_ptr> m_renderables;
    std::vector<texture_ptr> m_textures;

    renderer_ptr m_renderer;
    Camera m_camera;
};

} }

#endif /* GRAPHICS_LAYER_H_ */
