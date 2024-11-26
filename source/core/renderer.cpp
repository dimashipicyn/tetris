#include "renderer.h"

Renderer::Renderer(int width, int height)
    : m_window_width(width)
    , m_window_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
        return;
    }

    if (SDL_CreateWindowAndRenderer(m_window_width, m_window_height, 0, &m_window, &m_renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        return;
    }

    /*const auto view = SDL_Rect { 0, 0, 50, 50 };
    SDL_RenderSetViewport(m_renderer, &view);*/
    //SDL_RenderSetScale(m_renderer, 10, 10);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}