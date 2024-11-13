#include "texture.h"

void Texture::Draw(Renderer* renderer)
{
    SDL_RenderCopy(renderer->m_renderer, m_tex_handle, &m_src_rect, &m_dest_rect);
}