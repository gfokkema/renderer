#ifndef GL_CONTEXT_H_
#define GL_CONTEXT_H_

#include "common.h"

#include "program.h"
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

    void draw(Camera&, ObjModel&);
private:
    Program program;
    VertexArray vao;
    VertexBuffer vbo;
    VertexBuffer vbo_index;
};

#endif /* GL_CONTEXT_H_ */
