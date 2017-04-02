#include "renderer3d.h"

graphics::Renderer3D::Renderer3D(std::vector<texture> textures)
: Renderer(std::move(textures))
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

graphics::Renderer3D::~Renderer3D()
{
}

// FIXME: Camera should be const, but camera.matrix() updates stuff.
//        Might therefore move updating the camera into the main render loop.
void
graphics::Renderer3D::draw(graphics::Camera & camera)
{
    auto model = glm::mat4(1.0f);
    auto mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto it = this->m_renderables.begin();
    while (it != this->m_renderables.end())
    {
        auto& renderable = *it++;
        auto& program = *(renderable->program());
        auto& vao = renderable->vao();

        program.use();
        program["mvp"].set(mvp);
        program["tex"].set(vao.texture_idx);

        vao.bind();
        glDrawElements(
            GL_TRIANGLES,    // mode
            vao.m_size,      // count
            GL_UNSIGNED_INT, // type
            (void*)0         // element array buffer offset
        );
        vao.unbind();

        this->m_renderables.pop_front();
    }
}

void
graphics::Renderer3D::submit(std::vector<renderable>& renderables)
{
    for (auto& renderable : renderables)
        this->m_renderables.push_back(renderable);
}
