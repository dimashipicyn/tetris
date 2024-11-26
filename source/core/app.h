#pragma once

#include "sdl.h"
#include "assets.h"
#include "renderer.h"
#include "scene.h"

class App
{
public:
    bool Init();
    void Run();

    static Assets* Assets;
    static Renderer* Renderer;
    static Scene* Scene;

protected:
    virtual void OnInit() = 0;
    virtual void OnInput() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

private:
    void Input();
    void Update();
    void Render();

    int64_t m_ticks {};

    int m_step_time_ms = 16;

    bool m_running = true;
};