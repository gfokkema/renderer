#include "util/objmodel.h"
#include "window.h"

int main(int argc, char** argv)
{
    gl::Window window;
    gl::Context ctx;
    util::Input input;
    util::ObjModel model;

    if (window.create(input) != STATUS_OK)
    {
        std::cerr << "Failed to create window." << std::endl;
        return STATUS_ERR;
    }

    model.load("../Desmond_Miles/", "Desmond_Miles.obj");
    if (ctx.create(model) != STATUS_OK)
    {
        std::cerr << "Failed to create opengl context." << std::endl;
        return STATUS_ERR;
    }

    do {
        double start = glfwGetTime();
        ctx.draw(window.camera());
        std::cout << "frame draw took " << glfwGetTime() - start << " seconds.\r";
        std::flush(std::cout);

        if (input[GLFW_KEY_A]) window.camera().left();
        if (input[GLFW_KEY_D]) window.camera().right();
        if (input[GLFW_KEY_W]) window.camera().forward();
        if (input[GLFW_KEY_S]) window.camera().backward();
        if (input[GLFW_KEY_ESCAPE]) window.close();

        window.refresh();
        window.update();
    } while (window.should_close() != STATUS_OK);

    window.destroy();
    ctx.destroy();

    return STATUS_OK;
}
