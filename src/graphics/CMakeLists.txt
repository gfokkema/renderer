# -- graphics/CMakeLists.txt
#
add_subdirectory (layers)

file (GLOB WINDOW_SOURCES *.cpp)
add_library (window ${WINDOW_SOURCES})
target_link_libraries (window window_layers graphics epoxy ${GLFW_LIBRARIES})
