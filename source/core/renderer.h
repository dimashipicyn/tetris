#pragma once

#include "math/size.h"
#include "math/rect.h"
#include "color.h"

#include <SDL_render.h>

class Texture;

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    void DrawTexture(const Texture& tex, const Rect& src, const Rect& dest);
    void DrawTexture(const Texture& tex);

    void DrawPoint(const SDL_Point& p, const Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(m_renderer, p.x, p.y);
    }

    void DrawLine(const SDL_Point& p1, const SDL_Point& p2, const Color& color)
    {
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(m_renderer, p1.x, p1.y, p2.x, p2.y);
    }

    void DrawRect(const SDL_Rect& r, const Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(m_renderer, &r);
    }

    void DrawFillRect(const SDL_Rect& r, const Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(m_renderer, &r);
    }

    void Clear();
    void Present();

    const Size& GetWindowSize() const
    {
        return m_window_size;
    }

private:
    friend class Assets;

    SDL_Renderer* m_renderer {};
    SDL_Window* m_window {};

    Size m_window_size{800, 600};
};