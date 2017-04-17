#include "renderer.h"

void graphics::Renderer::submit(image_buffer_ptr& buffer)
{
    glActiveTexture(GL_TEXTURE0 + this->m_textures.size());

    auto texture = std::make_unique<gl::Texture>(GL_TEXTURE_2D);
    texture->bind();
    texture->upload(buffer);

    this->m_textures.push_back(std::move(texture));
}
