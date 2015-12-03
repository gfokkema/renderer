#include "window.h"

#include <iostream>

int main(int argc, char** argv) {
    Window window;

    if (!window.create())
    {
        std::cerr << "Failed to create window." << std::endl;
        return -1;
    }
    window.init();

    // std::vector<tinyobj::shape_t> shapes;
    // std::vector<tinyobj::material_t> materials;

    std::string err;
    // Load our model
    // if (!tinyobj::LoadObj(shapes, materials, err, "../altair.obj", "../")) {
        // std::cerr << "Failed to load obj: " << err << std::endl;
        // return -1;
    // }
    // std::cout << "# shapes   : " << shapes.size() << std::endl;
    // std::cout << "# materials: " << materials.size() << std::endl;
    // for (auto i = 0; i < shapes.size(); i++) {
        // std::cout << i << " name: " << shapes[i].name << std::endl;
        // std::cout << "  size: " << shapes[i].mesh.positions.size() << std::endl;
    // }


    // Set the timer to zero
    glfwSetTime(0.0);
    double prev = 0;
    unsigned frames = 0;
    do {
        window.draw();
        window.update();

        double cur = glfwGetTime();
        // handle_input(cur - prev);

        // std::cout << "FPS: " << ++frames / cur << "\r";
        // std::flush(std::cout);
        prev = cur;
    } while (!window.shouldClose());

    window.destroy();
}
