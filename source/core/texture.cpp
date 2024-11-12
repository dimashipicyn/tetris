#include "texture.h"

void Texture::Draw(Renderer* renderer)
{
    SDL_RenderCopy(renderer->m_renderer, m_tex_handle, NULL, &m_tex_rect);
}