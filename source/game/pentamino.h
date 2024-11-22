#pragma once

#include "core/texture.h"
#include "core/assets.h"
#include "core/renderer.h"

#include <array>
#include <cstdint>

using PentaminoDef = std::array<SDL_Point, 5>;

constexpr const PentaminoDef L_Pentamino = {
    {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
        { 0, 3 },
        { 1, 3 },
    }
};

constexpr const PentaminoDef N_Pentamino = {
    {
        { 1, 0 },
        { 1, 1 },
        { 1, 2 },
        { 0, 2 },
        { 0, 3 },
    }
};


//, P, F, Y, T, V, U, W, Z, I, X

class Pentamino
{
public:
    Pentamino(Assets* assets, PentaminoDef def)
        : m_def {def}
    {
        m_texture = assets->LoadTexture("images/block.png", {32, 32});
    }

    void Draw(Renderer* renderer);

private:
    Texture m_texture {};
    PentaminoDef m_def {};
};