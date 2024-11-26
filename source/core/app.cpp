#include "app.h"

Assets* App::Assets;
Renderer* App::Renderer;
Scene* App::Scene;

bool App::Init()
{
    Renderer = new ::Renderer(800, 600);
    Assets = new ::Assets(Renderer);
    Scene = new ::Scene;

    OnInit();
    return true;
}

void App::Run()
{
    m_prev_ticks = SDL_GetTicks();
    while (m_running)
    {
        auto now = SDL_GetTicks();
        auto elapsed = now - m_prev_ticks;
        m_prev_ticks = now;
        
        Input();
        
        m_ticks_acc += elapsed;
        while (m_ticks_acc >= m_step_time_ms)
        {
            Update();
            m_ticks_acc -= m_step_time_ms;
        }

        Render();

        int delay = m_frame_time_ms - elapsed;
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
    Scene->Update();
    OnUpdate();
}

void App::Render()
{
    Renderer->Clear();

    Scene->Draw(Renderer);
    OnRender();
    
    Renderer->Present();
}
