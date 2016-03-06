#include "msg/channel.h"
#include "msg/movement.h"

#include "util/objmodel.h"
#include "window.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    util::Input input;
    gl::Window window(input);
    gl::Window window2(input);

    util::ObjModel model("../Desmond_Miles/", "Desmond_Miles.obj");
    window.activate();
    gl::Context ctx(model);

    window2.activate();
    gl::Context ctx2(model);

    Channel<Movement> channel;
    channel.listen(&window.camera());
    do {
        double frame_end = glfwGetTime() + 1.0 / 60.0;

        if (input[GLFW_KEY_A]) channel.emit(&LEFT);
        if (input[GLFW_KEY_D]) channel.emit(&RIGHT);
        if (input[GLFW_KEY_W]) channel.emit(&FORWARD);
        if (input[GLFW_KEY_S]) channel.emit(&BACKWARD);
        if (input[GLFW_KEY_ESCAPE]) window.close();

        double start = glfwGetTime();
        window.activate();
        ctx.draw(window.camera());
        window.refresh();
        window.update();

        window2.activate();
        ctx2.draw(window2.camera());
        window2.refresh();
        window2.update();
        double end = glfwGetTime();

        std::cout << "Frame draw took " << end - start << " seconds.\r";
        std::flush(std::cout);

        unsigned ns = std::max(0., (frame_end - glfwGetTime()) * 1e9);
        std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
    } while (!window.should_close());

    return EXIT_SUCCESS;
}
