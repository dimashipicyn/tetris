#include "app.h"
#include "provider.h"
#include "state.h"

bool App::Init(const Size& window_size)
{
    Renderer = new ::Renderer(window_size.x, window_size.y);
    Assets = new ::Assets(Renderer);
    Input = new ::Input();
    StateManager = new ::StateManager(*this);
    Ui = new ::Ui;

    Provider::Self().m_renderer = Renderer;
    Provider::Self().m_assets = Assets;
    Provider::Self().m_input = Input;
    Provider::Self().m_state_manager = StateManager;
    Provider::Self().m_ui = Ui;
    Provider::Self().m_app = this;

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
    StateManager->CurrentState()->Update(*this);
}

void App::Render()
{
    Renderer->Clear();

    OnRender();
    StateManager->CurrentState()->Draw(*this);
    
    Renderer->Present();
}
