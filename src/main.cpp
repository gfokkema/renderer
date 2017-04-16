#include <chrono>
#include <iostream>
#include <thread>

#include "common.h"

#include "graphics/layers/layer.h"
#include "graphics/window.h"
#include "msg/channel.h"
#include "msg/movement.h"
#include "util/file.h"
#include "util/objmodel.h"

using namespace graphics;

int main(int argc, char** argv)
{
    Channel<Movement> channel;
    graphics::Window window;
    window.activate();

    util::ObjModel model("../Desmond_Miles/", "Desmond_Miles.obj");
    gl::Shader vertexshader(GL_VERTEX_SHADER);
    gl::Shader fragmentshader(GL_FRAGMENT_SHADER);
    vertexshader.load(util::File("../src/shaders/shader.vertex.c").read());
    fragmentshader.load(util::File("../src/shaders/shader.fragment.c").read());

    auto program = std::make_shared<gl::Program>();
    program->load(vertexshader, fragmentshader);
    program->resolve();

    graphics::layers::Layer layer(std::make_unique<SimpleRenderer3D>(), program);
    for (auto& material : model.m_materials)
        layer.add(material.get_buffer(util::IMAGE_MAP::DIFFUSE));
    for (auto& shape : model.m_shapes)
        layer.add(std::make_shared<SimpleRenderable3D>(program, shape));

    channel.listen(&layer.camera());
    do {
        double frame_end = glfwGetTime() + 1.0 / 60.0;

        if (window.input()[GLFW_KEY_A]) channel.emit(&LEFT);
        if (window.input()[GLFW_KEY_D]) channel.emit(&RIGHT);
        if (window.input()[GLFW_KEY_W]) channel.emit(&FORWARD);
        if (window.input()[GLFW_KEY_S]) channel.emit(&BACKWARD);
        if (window.input()[GLFW_KEY_ESCAPE]) window.close();

        double start = glfwGetTime();
        window.activate();
        layer.render();
        window.update();
        double end = glfwGetTime();

        printf("Frame draw took %f ms.\r", (end - start) * 1e3);
        std::flush(std::cout);

        unsigned ns = std::max(0., (frame_end - glfwGetTime()) * 1e9);
        std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
    } while (!window.should_close());

    return EXIT_SUCCESS;
}
