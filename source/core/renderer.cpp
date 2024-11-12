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
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Renderer::Clear()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}