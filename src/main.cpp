#include "window.h"

#include <iostream>

#include "status.h"
#include "tiny_obj_loader.h"

Status loadobj()
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    // Load our model
    if (!tinyobj::LoadObj(shapes, materials, err, "../altair.obj", "../")) {
        std::cerr << "Failed to load obj: " << err << std::endl;
        return STATUS_ERR;
    }
    std::cout << "# shapes   : " << shapes.size() << std::endl;
    std::cout << "# materials: " << materials.size() << std::endl;
    for (auto i = 0; i < shapes.size(); i++) {
        std::cout << i << " name: " << shapes[i].name << std::endl;
        std::cout << "  size: " << shapes[i].mesh.positions.size() << std::endl;
    }

    return STATUS_OK;
}

int main(int argc, char** argv) {
    Window window;

    if (window.create() != STATUS_OK)
    {
        std::cerr << "Failed to create window." << std::endl;
        return STATUS_ERR;
    }

    window.init();
    loadobj();

    // Set the timer to zero
    glfwSetTime(0.0);
    unsigned frames = 0;
    do {
        window.draw();
        window.update();

        // Overflows after a while.
        std::cout << "FPS: " << ++frames / glfwGetTime() << "\r";
        std::flush(std::cout);
    } while (window.shouldClose() != STATUS_OK);

    window.destroy();

    return STATUS_OK;
}
