#ifndef RENDERER3D_H_
#define RENDERER3D_H_

#include "renderer.h"
#include "advrenderable3d.h"

namespace graphics
{

class Renderer3D : public Renderer
{
public:
    Renderer3D();
    virtual ~Renderer3D();

    void submit(std::vector<renderable_ptr>& renderables) override;
    void submit(image_buffer_ptr& buffer) override;
    void draw(Camera &) override;
private:
    gl::Shader vertexshader;
    gl::Shader fragmentshader;
    gl::Program program;

    gl::VertexArray m_vao;
    gl::VertexBuffer m_vbo;
    gl::VertexBuffer m_ibo;

    std::list<renderable_ptr> m_renderables;

    std::vector<gl::VertexData> m_vertexdata;
    std::vector<unsigned> m_indexdata;
};

}

#endif /* RENDERER3D_H_ */
