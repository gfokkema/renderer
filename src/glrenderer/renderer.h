#ifndef GL_RENDERER_H_
#define GL_RENDERER_H_

#include "common.h"

#include "gl/texture.h"
#include "util/camera.h"
#include "util/objmodel.h"
#include "renderable3d.h"

namespace glrenderer
{

class Renderer
{
public:
    Renderer(const util::ObjModel &);
    ~Renderer();

    void draw(util::Camera &);
private:
    std::vector<std::shared_ptr<glrenderer::Renderable3D>> renderables;
    std::vector<std::shared_ptr<gl::Texture>> textures;
};

}

#endif /* GL_RENDERER_H_ */
