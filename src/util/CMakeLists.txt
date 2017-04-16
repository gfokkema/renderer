# -- util/CMakeLists.txt
#
file (GLOB UTIL_SOURCES *.cpp)
add_library (util ${UTIL_SOURCES})
target_link_libraries (util fmt freeimage)
