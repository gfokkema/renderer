#ifndef GLRENDERER_RENDERABLE3D_H_
#define GLRENDERER_RENDERABLE3D_H_

#include "common.h"

#include "gl/program.h"
#include "gl/vertexbuffer.h"
#include "gl/vertexarray.h"
#include "tiny_obj_loader.h"

namespace glrenderer
{

class Renderable3D
{
public:
    Renderable3D(std::shared_ptr<gl::Program> program, tinyobj::shape_t& shape, glm::vec3 pos = glm::vec3(0, 0, 0));
    virtual ~Renderable3D();

    std::shared_ptr<gl::Program>& program();
    gl::VertexArray& vao();
private:
    std::shared_ptr<gl::Program> m_program;
    gl::VertexArray m_vao;
    gl::VertexBuffer m_vbo;
    gl::VertexBuffer m_uv;
    gl::VertexBuffer m_ibo;
    glm::vec3 m_pos;
};

}

#endif /* GLRENDERER_RENDERABLE3D_H_ */
