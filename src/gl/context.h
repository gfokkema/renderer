#ifndef GL_CONTEXT_H_
#define GL_CONTEXT_H_

#include "common.h"

#include "program.h"
#include "vertexarray.h"
#include "vertexbuffer.h"


class Context {
public:
    Context ();
    ~Context ();

    Status create();
    void destroy();

    Program program;
    VertexArray vao;
    VertexBuffer vbo;
};

#endif /* GL_CONTEXT_H_ */
