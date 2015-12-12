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

class Context {
public:
    Context ();
    ~Context ();

    Status create(std::vector<tinyobj::shape_t>,
                  std::vector<tinyobj::material_t>);
    void destroy();

    void draw(Camera&);
private:
    VertexArray* create(tinyobj::shape_t);
    Texture* create(tinyobj::material_t);

    Program program;
    std::vector<Texture*> textures;
    std::vector<VertexArray*> vao_array;
};

#endif /* GL_CONTEXT_H_ */
