#ifndef GL_RENDERER_H_
#define GL_RENDERER_H_

#include "common.h"

#include "gl/texture.h"
#include "renderer.h"

namespace graphics
{

class Renderer3D : public Renderer
{
public:
    Renderer3D(std::vector<texture> textures);
    ~Renderer3D();

    void draw(Camera &) override;
    void submit(std::vector<renderable>& renderables) override;
private:
    std::list<renderable> m_renderables;
};

}

#endif /* GL_RENDERER_H_ */
