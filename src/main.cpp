#include "util/objmodel.h"
#include "window.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    util::Input input;
    gl::Window window(input);

    util::ObjModel model("../Ciri/", "ciri.obj");
    gl::Context ctx(model);

    do {
        double frame_end = glfwGetTime() + 1.0 / 60.0;

        if (input[GLFW_KEY_A]) window.camera().left();
        if (input[GLFW_KEY_D]) window.camera().right();
        if (input[GLFW_KEY_W]) window.camera().forward();
        if (input[GLFW_KEY_S]) window.camera().backward();
        if (input[GLFW_KEY_ESCAPE]) window.close();

        double start = glfwGetTime();
        ctx.draw(window.camera());
        window.refresh();
        window.update();
        double end = glfwGetTime();

        std::cout << "Frame draw took " << end - start << " seconds.\r";
        std::flush(std::cout);

        std::chrono::nanoseconds duration((unsigned)((frame_end - glfwGetTime()) * 1e9));
        std::this_thread::sleep_for(duration);
    } while (!window.should_close());

    return EXIT_SUCCESS;
}
