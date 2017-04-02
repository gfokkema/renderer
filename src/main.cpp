#include "msg/channel.h"
#include "msg/movement.h"

#include "util/objmodel.h"
#include "window.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    util::ObjModel model("../Desmond_Miles/", "Desmond_Miles.obj");

    gl::Window window;
    window.activate();
    gl::Context ctx(model);

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
        ctx.draw(window.camera());
        window.update();

        double end = glfwGetTime();

        std::cout << "Frame draw took " << end - start << " seconds.\r";
        std::flush(std::cout);

        unsigned ns = std::max(0., (frame_end - glfwGetTime()) * 1e9);
        std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
    } while (!window.should_close());

    return EXIT_SUCCESS;
}
