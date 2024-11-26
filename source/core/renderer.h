#pragma once

#include "sdl.h"

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    //void DrawTexture(const Texture& tex, SDL_Point pos, SDL_FPoint scale = { 1, 1 });

    void DrawPoint(const SDL_Point& p, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
        SDL_RenderDrawPoint(m_renderer, p.x, p.y);
    }

    void DrawLine(const SDL_Point& p1, const SDL_Point& p2, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
        SDL_RenderDrawLine(m_renderer, p1.x, p1.y, p2.x, p2.y);
    }

    void DrawRect(const SDL_Rect& r, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
        SDL_RenderDrawRect(m_renderer, &r);
    }

    void DrawFillRect(const SDL_Rect& r, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
        SDL_RenderFillRect(m_renderer, &r);
    }

    void Clear();
    void Present();

private:
    friend class Texture;
    friend class Assets;

    SDL_Renderer* m_renderer {};
    SDL_Window* m_window {};

    int m_window_width = 800;
    int m_window_height = 600;
};