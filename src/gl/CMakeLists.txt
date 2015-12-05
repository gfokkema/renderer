file (GLOB GL_SOURCES *.cpp)
add_library (gl ${GL_SOURCES})
target_link_libraries (gl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})