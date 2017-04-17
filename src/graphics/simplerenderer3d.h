#ifndef GL_RENDERER_H_
#define GL_RENDERER_H_

#include "gl/gl.h"
#include "renderer.h"
#include "simplerenderable3d.h"

namespace graphics
{

class SimpleRenderer3D : public Renderer
{
public:
    SimpleRenderer3D();
    ~SimpleRenderer3D();

    void submit(std::vector<renderable_ptr>& renderables) override;
    void draw(Camera &) override;
private:
    std::list<simple_renderable_ptr> m_renderables;
};

}

#endif /* GL_RENDERER_H_ */
