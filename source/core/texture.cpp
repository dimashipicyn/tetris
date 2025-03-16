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
