file (GLOB GL_SOURCES *.cpp)
add_library (gl ${GL_SOURCES})
target_link_libraries (gl epoxy freeimage ${OPENGL_LIBRARIES})
