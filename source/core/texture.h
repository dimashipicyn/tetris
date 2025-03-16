#pragma once

#include "renderer.h"
#include "sdl.h"

#include <SDL_render.h>
#include <memory>

class Texture
{
    friend class Renderer;
public:
    Texture(SDL_Texture* tex = nullptr);

    SDL_Rect Dest {};
    SDL_Rect Src {};

    void SetColor(const Color& color) {
        SDL_SetTextureColorMod(m_tex_handle.get(), color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(m_tex_handle.get(), color.a);
    }

private:
    using TextureHandlePtr = std::shared_ptr<SDL_Texture>;
    TextureHandlePtr m_tex_handle {};
};