#include "texture.h"

Texture::Texture(SDL_Texture* tex)
    : m_tex_handle(tex, SDL_DestroyTexture)
{
    if (!tex)
    {
        return;
    }

    if (SDL_QueryTexture(m_tex_handle.get(), NULL, NULL, &Src.w, &Src.h))
    {
        SDL_Log("Texture::SDL_QueryTexture() failed: %s\n", SDL_GetError());
    }
    Dest.w = Src.w;
    Dest.h = Src.h;
}

void Texture::Draw(Renderer* renderer)
{
    SDL_Rect dest { Dest.x, Dest.y,
        static_cast<int>(Dest.w * Scale.x),
        static_cast<int>(Dest.h * Scale.y) };
    SDL_RenderCopy(renderer->m_renderer, m_tex_handle.get(), &Src, &dest);
}