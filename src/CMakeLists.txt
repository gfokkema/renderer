cmake_minimum_required (VERSION 2.6)
project (renderer)

add_definitions(-std=c++11 -O3)

find_package (OpenGL REQUIRED)
find_package (PkgConfig REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)
pkg_search_module (GLEW REQUIRED glew)

include_directories (external/tinyobjloader)
add_subdirectory (external/tinyobjloader)

include_directories (${PROJECT_SOURCE_DIR})

add_subdirectory (gl)

add_executable (renderer main.cpp window.cpp)
target_link_libraries (renderer gl tinyobjloader ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
