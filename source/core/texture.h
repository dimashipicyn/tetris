#pragma once

#include "renderer.h"
#include "sdl.h"
#include <memory>

class Texture
{
public:
    Texture(SDL_Texture* tex = nullptr)
        : m_tex_handle(tex)
    {
        int w, h;
        if (!SDL_QueryTexture(m_tex_handle, NULL, NULL, &w, &h))
        {
            SetSize({ w, h });
        }
    }
    
    void SetPos(const SDL_Point& pos)
    {
        m_tex_rect.x = pos.x;
        m_tex_rect.y = pos.y;
    }

    void SetSize(const SDL_Point& size)
    {
        m_tex_rect.w = size.x;
        m_tex_rect.h = size.y;
    }

    void Draw(Renderer* renderer);

private:
    SDL_Texture* m_tex_handle {};
    SDL_Rect m_tex_rect;
};