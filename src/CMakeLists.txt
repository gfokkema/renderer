# -- CMakeLists.txt
#
cmake_minimum_required (VERSION 2.6)
project (renderer)

add_definitions(-std=c++14 -g)

find_package (OpenGL REQUIRED)
find_package (PkgConfig REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)

# Please note the following implicit dependencies:
# - epoxy (src/gl/CMakeLists.txt)
# - freeimage (src/gl/CMakeLists.txt)

include_directories (external/format)
add_subdirectory (external/format)
include_directories (external/tinyobjloader)
add_subdirectory (external/tinyobjloader)

include_directories (${PROJECT_SOURCE_DIR})

add_subdirectory (msg)
add_subdirectory (graphics)
add_subdirectory (util)

file (GLOB SOURCES *.cpp)
add_executable (renderer ${SOURCES})
target_link_libraries (renderer graphics msg util tinyobjloader)
