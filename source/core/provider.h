#pragma once

class Renderer;
class Assets;
class Input;
class StateManager;

class Provider
{
    friend class App;

public:
    static Provider& Self();

    ::Renderer* Renderer()
    {
        return m_renderer;
    }

    ::Assets* Assets()
    {
        return m_assets;
    }

    ::Input* Input()
    {
        return m_input;
    }

    ::StateManager* StateManager()
    {
        return m_state_manager;
    }

private:
    Provider() = default;
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;

    ::Renderer* m_renderer {};
    ::Assets* m_assets {};
    ::Input* m_input {};
    ::StateManager* m_state_manager {};
};