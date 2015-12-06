file (GLOB GL_SOURCES *.cpp)
add_library (gl ${GL_SOURCES})
target_link_libraries (gl freeimage ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
