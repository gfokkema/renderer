#include "simplerenderer3d.h"

graphics::SimpleRenderer3D::SimpleRenderer3D()
{
}

graphics::SimpleRenderer3D::~SimpleRenderer3D()
{
}

void
graphics::SimpleRenderer3D::submit(std::vector<renderable_ptr>& renderables)
{
    for (auto& renderable : renderables)
        this->m_renderables.push_back(std::static_pointer_cast<SimpleRenderable3D>(renderable));
}

// FIXME: Camera should be const, but camera.matrix() updates stuff.
//        Might therefore move updating the camera into the main render loop.
void
graphics::SimpleRenderer3D::draw(graphics::Camera& camera)
{
    auto model = glm::mat4(1.0f);
    auto mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto it = this->m_renderables.begin();
    while (it != this->m_renderables.end())
    {
        auto& renderable = *it++;
        auto& program = *(renderable->program());
        auto  texid = renderable->texid();
        auto& vao = renderable->vao();

        program.use();
        program["mvp"].set(mvp);
        program["tex"][0].set(texid);

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
