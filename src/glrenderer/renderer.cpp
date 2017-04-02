#include "renderer.h"

glrenderer::Renderer::Renderer(const util::ObjModel & model)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    gl::Shader vertexshader(GL_VERTEX_SHADER);
    gl::Shader fragmentshader(GL_FRAGMENT_SHADER);
    vertexshader.load("../src/shaders/shader.vertex.c");
    fragmentshader.load("../src/shaders/shader.fragment.c");

    auto program = std::make_shared<gl::Program>();
    program->load(vertexshader, fragmentshader);
    program->resolve();

    for (auto shape : model.m_shapes)
    {
        renderables.push_back(std::make_shared<Renderable3D>(program, shape, glm::vec3(0, 0, 0)));
    }

    // load textures
    for (auto idx = 0; idx < model.m_materials.size(); idx++)
    {
        auto mat = model.m_materials.begin() + idx;
        glActiveTexture(GL_TEXTURE0 + idx);

        auto texture = std::make_shared<gl::Texture>(GL_TEXTURE_2D);
        texture->bind();
        texture->upload(mat->get_buffer(util::IMAGE_MAP::DIFFUSE));

        this->textures.push_back(texture);
    }
}

glrenderer::Renderer::~Renderer()
{
}

// FIXME: Camera should be const, but camera.matrix() updates stuff.
//        Might therefore move updating the camera into the main render loop.
void
glrenderer::Renderer::draw(util::Camera & camera)
{
    auto model = glm::mat4(1.0f);
    auto mvp = camera.matrix() * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto renderable : this->renderables)
    {
        gl::Program& program = *(renderable->program());
        program.use();
        program["mvp"].set(mvp);
        program["tex"].set(renderable->vao().texture_idx);

        renderable->vao().bind();
        glDrawElements(
            GL_TRIANGLES,            // mode
            renderable->vao().m_size,             // count
            GL_UNSIGNED_INT,         // type
            (void*)0                 // element array buffer offset
        );
        renderable->vao().unbind();
    }
}
