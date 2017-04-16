# -- graphics/CMakeLists.txt
#
add_subdirectory (gl)
add_subdirectory (layers)

file (GLOB GRAPHICS_SOURCES *.cpp)
add_library (graphics ${GRAPHICS_SOURCES})
target_link_libraries (graphics layers gl fmt epoxy ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
