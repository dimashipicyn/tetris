#pragma once

#include "core/sprite.h"

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

class Pentamino : public Sprite
{
public:
    Pentamino(PentaminoDef def, SceneObject* parent = nullptr)
        : Sprite("images/block.png", parent, {32, 32})
        , m_def {def}
    {
    }

    void Update() override;
    void Draw(Renderer* renderer) override;

private:
    PentaminoDef m_def {};
};