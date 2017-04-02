# -- graphics/CMakeLists.txt
#
add_subdirectory (gl)

file (GLOB GRAPHICS_SOURCES *.cpp)
add_library (graphics ${GRAPHICS_SOURCES})
target_link_libraries (graphics gl epoxy ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
