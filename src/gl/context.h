#ifndef GL_CONTEXT_H_
#define GL_CONTEXT_H_

#include "common.h"

#include "program.h"
#include "texture.h"
#include "tiny_obj_loader.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "util/camera.h"
#include "util/objmodel.h"

namespace gl
{

class Context
{
public:
    Context(util::ObjModel);
    ~Context();

    void draw(util::Camera&);
private:
    void create(tinyobj::shape_t);

    gl::Program program;
    std::vector<std::shared_ptr<gl::Texture>> textures;
    std::vector<std::shared_ptr<VertexArray>> vao_array;
    std::vector<std::shared_ptr<VertexBuffer>> vbo_array;
};

}

#endif /* GL_CONTEXT_H_ */
