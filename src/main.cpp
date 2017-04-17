#include <chrono>
#include <iostream>
#include <thread>

#include "common.h"

#include "graphics/layers/layer.h"
#include "graphics/renderer3d.h"
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

//    util::ObjModel model("../", "cubes.obj");
    util::ObjModel model("../Desmond_Miles/", "Desmond_Miles.obj");
    graphics::layers::Layer layer(std::make_unique<Renderer3D>());

    for (auto& material : model.m_materials)
        layer.add(material.get_buffer(util::IMAGE_MAP::DIFFUSE));
    for (auto& shape : model.m_shapes)
        layer.add(std::make_shared<AdvRenderable3D>(shape)); // model.m_shapes[3]));

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
