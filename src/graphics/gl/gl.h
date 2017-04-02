#ifndef GRAPHICS_GL_GL_H_
#define GRAPHICS_GL_GL_H_

#include "common.h"

#include "program.h"
#include "shader.h"
#include "texture.h"
#include "uniform.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

typedef std::shared_ptr<graphics::gl::image_buffer> image_buffer_ptr;
typedef std::shared_ptr<graphics::gl::Program> program_ptr;
typedef std::unique_ptr<graphics::gl::Texture> texture_ptr;

#endif /* GRAPHICS_GL_GL_H_ */
