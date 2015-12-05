#include "status.h"
#include "tiny_obj_loader.h"
#include "window.h"

Status loadobj()
{
    std::string err;

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    // Load our model
    if (!tinyobj::LoadObj(shapes, materials, err, "../altair.obj", "../"))
    {
        std::cerr << "Failed to load obj: " << err << std::endl;
        return STATUS_ERR;
    }
    std::cout << "# shapes   : " << shapes.size() << std::endl;
    std::cout << "# materials: " << materials.size() << std::endl;

    for (auto i = 0; i < shapes.size(); i++)
    {
        std::cout << i << " name: " << shapes[i].name << std::endl;
        std::cout << "  size: " << shapes[i].mesh.positions.size() << std::endl;
    }

    return STATUS_OK;
}

int main(int argc, char** argv)
{
    loadobj();

    Window window;
    Context ctx;

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

    unsigned frames = 0;
    do {
        window.draw(ctx);
        window.update();

        // Overflows after a while.
        std::cout << "FPS: " << ++frames / glfwGetTime() << "\r";
        std::flush(std::cout);
    } while (window.shouldClose() != STATUS_OK);

    window.destroy();
    ctx.destroy();

    return STATUS_OK;
}
