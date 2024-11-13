#pragma once

#include "sdl.h"

class Renderer
{
public:
    Renderer(int width, int height);
    ~Renderer();

    //void DrawTexture(const Texture& tex, SDL_Point pos, SDL_FPoint scale = { 1, 1 });

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