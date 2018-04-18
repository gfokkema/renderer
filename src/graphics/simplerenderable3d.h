#ifndef GRAPHICS_SIMPLERENDERABLE3D_H_
#define GRAPHICS_SIMPLERENDERABLE3D_H_

#include <graphics/gl/program.h>
#include <graphics/gl/vertexarray.h>
#include <graphics/gl/vertexbuffer.h>

#include "renderable3d.h"
#include "tiny_obj_loader.h"

namespace graphics {

class SimpleRenderable3D : public Renderable3D
{
public:
    SimpleRenderable3D(program_ptr& program, tinyobj::shape_t& shape, glm::vec3 pos = glm::vec3(0));
    virtual ~SimpleRenderable3D();

    std::shared_ptr<gl::Program>& program();
    gl::VertexArray& vao();
private:
    std::shared_ptr<gl::Program> m_program;
    gl::VertexArray m_vao;
    gl::VertexBuffer m_vbo;
    gl::VertexBuffer m_uv;
    gl::VertexBuffer m_ibo;
};

}

#endif /* GRAPHICS_SIMPLERENDERABLE3D_H_ */
