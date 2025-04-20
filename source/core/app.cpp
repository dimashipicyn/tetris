#include "app.h"

bool App::Init(const Size& window_size)
{
    Renderer = new ::Renderer(window_size.x, window_size.y);
    Assets = new ::Assets(Renderer);
    Input = new ::Input();

    OnInit();
    return true;
}

void App::Run()
{
    m_prev_ticks = SDL_GetTicks();
    while (m_running)
    {
        RunOnce();
    }
}

void App::RunOnce()
{
    auto now = SDL_GetTicks();
    auto elapsed = now - m_prev_ticks;
    m_prev_ticks = now;

    DeltaTime = elapsed / 1000.0f;

    HandleEvents();

    m_ticks_acc += elapsed;
    // while (m_ticks_acc >= m_step_time_ms)
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

void App::HandleEvents()
{
    Input->PollEvents();
    m_running = !Input->IsExit();
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
