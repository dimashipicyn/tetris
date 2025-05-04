#pragma once

class Renderer;
class Assets;

class Provider
{
    friend class App;
public:
    static Provider& Self();

    ::Renderer* Renderer() {
        return m_renderer;
    }

    ::Assets* Assets() {
        return m_assets;
    }

private:
    Provider() = default;
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;

    ::Renderer* m_renderer{};
    ::Assets* m_assets{};
};