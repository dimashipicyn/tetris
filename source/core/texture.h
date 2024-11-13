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

    /*void SetPos(const SDL_Point& pos)
    {
        m_dest_rect.x = pos.x;
        m_dest_rect.y = pos.y;
    }

    void SetDest(const SDL_Rect& dest)
    {
        m_dest_rect = dest;
    }

    void SetSrc(const SDL_Rect& src)
    {
        m_src_rect = src;
    }*/

    void Draw(Renderer* renderer);

private:
    using TextureHandlePtr = std::shared_ptr<SDL_Texture>;
    TextureHandlePtr m_tex_handle {};
};