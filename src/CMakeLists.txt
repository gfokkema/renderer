# -- CMakeLists.txt
#
cmake_minimum_required (VERSION 2.6)
project (renderer)

set (CMAKE_CXX_STANDARD 17)
add_definitions(-g)

find_package (fmt REQUIRED)
find_package (OpenGL REQUIRED)
find_package (PkgConfig REQUIRED)
pkg_search_module (epoxy REQUIRED epoxy)
pkg_search_module (GLFW REQUIRED glfw3)

# Please note the following implicit dependencies:
# - freeimage (src/gl/CMakeLists.txt)

include_directories (external/tinyobjloader)
add_subdirectory (external/tinyobjloader)

include_directories (${PROJECT_SOURCE_DIR})

add_subdirectory (msg)
add_subdirectory (util)
add_subdirectory (graphics)

file (GLOB SOURCES *.cpp)
add_executable (renderer ${SOURCES})
target_link_libraries (renderer window msg util tinyobjloader)
