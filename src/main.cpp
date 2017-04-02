#include <chrono>
#include <thread>

#include "common.h"

#include "graphics/window.h"
#include "msg/channel.h"
#include "msg/movement.h"
#include "util/file.h"
#include "util/objmodel.h"

using namespace graphics;

void
init_renderer(std::unique_ptr<Renderer>& renderer, std::vector<renderable>& renderables) {
    util::ObjModel model("../Desmond_Miles/", "Desmond_Miles.obj");
    gl::Shader vertexshader(GL_VERTEX_SHADER);
    gl::Shader fragmentshader(GL_FRAGMENT_SHADER);
    vertexshader.load(util::File("../src/shaders/shader.vertex.c").read());
    fragmentshader.load(util::File("../src/shaders/shader.fragment.c").read());

    auto program = std::make_shared<gl::Program>();
    program->load(vertexshader, fragmentshader);
    program->resolve();

    for (auto shape : model.m_shapes)
        renderables.push_back(std::make_shared<Renderable3D>(program, shape));

    std::vector<texture> textures;
    for (auto idx = 0; idx < model.m_materials.size(); idx++)
    {
        auto mat = model.m_materials.begin() + idx;
        glActiveTexture(GL_TEXTURE0 + idx);

        auto texture = new gl::Texture(GL_TEXTURE_2D);
        texture->bind();
        texture->upload(mat->get_buffer(util::IMAGE_MAP::DIFFUSE));

        textures.push_back(std::unique_ptr<gl::Texture>(texture));
    }
    renderer = std::make_unique<Renderer3D>(std::move(textures));
}

int main(int argc, char** argv)
{
    graphics::Window window;
    window.activate();

    std::unique_ptr<Renderer> renderer;
    std::vector<renderable> renderables;
    init_renderer(renderer, renderables);

    Channel<Movement> channel;
    channel.listen(&window.camera());
    do {
        double frame_end = glfwGetTime() + 1.0 / 60.0;

        if (window.input()[GLFW_KEY_A]) channel.emit(&LEFT);
        if (window.input()[GLFW_KEY_D]) channel.emit(&RIGHT);
        if (window.input()[GLFW_KEY_W]) channel.emit(&FORWARD);
        if (window.input()[GLFW_KEY_S]) channel.emit(&BACKWARD);
        if (window.input()[GLFW_KEY_ESCAPE]) window.close();

        double start = glfwGetTime();
        window.activate();
        renderer->submit(renderables);
        renderer->draw(window.camera());
        window.update();
        double end = glfwGetTime();

        printf("Frame draw took %f ms.\r", (end - start) * 1e3);
        std::flush(std::cout);

        unsigned ns = std::max(0., (frame_end - glfwGetTime()) * 1e9);
        std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
    } while (!window.should_close());

    return EXIT_SUCCESS;
}
