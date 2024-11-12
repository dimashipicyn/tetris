#include "app.h"

bool App::Init()
{
    
    Renderer = new ::Renderer(800, 600);
    Assets = new ::Assets(Renderer);

    m_ticks = SDL_GetTicks();

    OnInit();
    return true;
}

void App::Run()
{
    while (m_running)
    {
        auto now = SDL_GetTicks();
        auto elapsed = now - m_ticks;
        
        Input();
        
        while ((now - m_ticks) >= m_step_time_ms)
        {
            Update();
            m_ticks += m_step_time_ms;
        }

        Render();

        auto delay = m_step_time_ms - elapsed;
        if (delay > 0)
        {
            SDL_Delay(delay);
        }
    }
}

void App::Input()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        default:
            break;
        }
    }
    OnInput();
}

void App::Update()
{
    OnUpdate();
}

void App::Render()
{
    Renderer->Clear();
    OnRender();
    Renderer->Present();
}
