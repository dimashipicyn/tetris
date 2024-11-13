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
        if (SDL_QueryTexture(m_tex_handle, NULL, NULL, &m_src_rect.w, &m_src_rect.h))
        {
            SDL_Log("SDL_QueryTexture() failed: %s\n", SDL_GetError());
        }
        m_dest_rect.w = m_src_rect.w;
        m_dest_rect.h = m_src_rect.h;
    }
    
    void SetPos(const SDL_Point& pos)
    {
        m_dest_rect.x = pos.x;
        m_dest_rect.y = pos.y;
    }

    void SetSize(const SDL_Point& size)
    {
        m_dest_rect.w = size.x;
        m_dest_rect.h = size.y;
    }

    void SetSrc(const SDL_Rect& src)
    {
        m_src_rect = src;
    }

    void Draw(Renderer* renderer);

private:
    SDL_Texture* m_tex_handle {};
    SDL_Rect m_dest_rect {};
    SDL_Rect m_src_rect {};
};