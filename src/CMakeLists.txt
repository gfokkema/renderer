cmake_minimum_required (VERSION 2.6)
project (renderer)

add_definitions(-std=c++11 -O3)

find_package (OpenGL REQUIRED)
find_package (PkgConfig REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)
pkg_search_module (GLEW REQUIRED glew)

add_executable (renderer loadshader.cpp window.cpp)
target_link_libraries (renderer ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
