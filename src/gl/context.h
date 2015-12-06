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

    Status create();
    void destroy();

    void draw(Camera&, std::vector<tinyobj::shape_t>);
private:
    Program program;
    Texture texture;
    VertexArray vao;
    VertexBuffer vbo;
    VertexBuffer vbo_index;
};

#endif /* GL_CONTEXT_H_ */
