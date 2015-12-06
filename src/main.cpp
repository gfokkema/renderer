#include "window.h"
#include "util/objmodel.h"

int main(int argc, char** argv)
{
    Window window;
    Context ctx;
    ObjModel model;

    if (window.create() != STATUS_OK)
    {
        std::cerr << "Failed to create window." << std::endl;
        return STATUS_ERR;
    }

    if (ctx.create() != STATUS_OK)
    {
        std::cerr << "Failed to create opengl context." << std::endl;
        return STATUS_ERR;
    }
    model.load();

    unsigned frames = 0;
    do {
        ctx.draw(window.camera(), model.m_shapes);
        window.refresh();
        window.update();

        // Overflows after a while.
        std::cout << "FPS: " << ++frames / glfwGetTime() << "\r";
        std::flush(std::cout);
    } while (window.should_close() != STATUS_OK);

    window.destroy();
    ctx.destroy();

    return STATUS_OK;
}
