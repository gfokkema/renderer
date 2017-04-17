# -- graphics/CMakeLists.txt
#
add_subdirectory (gl)
add_subdirectory (layers)
add_subdirectory (util)

file (GLOB GRAPHICS_SOURCES *.cpp)
add_library (graphics ${GRAPHICS_SOURCES})
target_link_libraries (graphics graphics_layers graphics_util gl fmt epoxy ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
