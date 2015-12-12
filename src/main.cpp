#include "util/objmodel.h"
#include "window.h"

int main(int argc, char** argv)
{
    gl::Window window;
    gl::Context ctx;
    util::ObjModel model;

    if (window.create() != STATUS_OK)
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

    unsigned frames = 0;
    do {
        double start = glfwGetTime();
        ctx.draw(window.camera());
        std::cout << "frame draw took " << glfwGetTime() - start << " seconds.\r";
        std::flush(std::cout);

        window.refresh();
        window.update();

        // Overflows after a while.
//        std::cout << "FPS: " << ++frames / glfwGetTime() << "\r";
//        std::flush(std::cout);
    } while (window.should_close() != STATUS_OK);

    window.destroy();
    ctx.destroy();

    return STATUS_OK;
}
