#pragma once

#include "renderer.h"
#include "sdl.h"

#include <memory>

class Texture
{
public:
    Texture(SDL_Texture* tex = nullptr);

    SDL_Rect Dest {};
    SDL_Rect Src {};
    SDL_FPoint Scale { 1.0f, 1.0f };

    void Draw(Renderer* renderer);

private:
    using TextureHandlePtr = std::shared_ptr<SDL_Texture>;
    TextureHandlePtr m_tex_handle {};
};