#include "layer.h"

graphics::layers::Layer::Layer(renderer_ptr renderer)
: m_renderer(std::move(renderer)), m_camera((float)WIDTH / (float)HEIGHT)
{
}

graphics::layers::Layer::~Layer()
{
}

void
graphics::layers::Layer::add(image_buffer_ptr buffer)
{
    glActiveTexture(GL_TEXTURE0 + this->m_textures.size());

    auto texture = std::make_unique<gl::Texture>(GL_TEXTURE_2D);
    texture->bind();
    texture->upload(buffer);

    this->m_textures.push_back(std::move(texture));
}

void
graphics::layers::Layer::add(renderable_ptr renderable)
{
    this->m_renderables.push_back(renderable);
}

void
graphics::layers::Layer::render()
{
    this->m_renderer->submit(this->m_renderables);
    this->m_renderer->draw(this->m_camera);
}

graphics::Camera&
graphics::layers::Layer::camera()
{
    return this->m_camera;
}
