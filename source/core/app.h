#pragma once

#include "assets.h"
#include "renderer.h"
#include "input.h"

class App
{
public:
    bool Init(const Size& window_size);
    void Run();
    void RunOnce();

    bool Running() {
        return m_running;
    }

    Assets* Assets;
    Renderer* Renderer;
    Input* Input;

    float DeltaTime{};

protected:
    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

private:
    void HandleEvents();
    void Update();
    void Render();

    uint32_t m_prev_ticks {};
    uint32_t m_ticks_acc {};

    uint32_t m_step_time_ms = 16;
    int32_t m_frame_time_ms = 16;

    bool m_running = true;
};