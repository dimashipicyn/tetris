#pragma once

#include "cell.h"

#include "core/app.h"
#include "core/assets.h"
#include "core/math/matrix.h"
#include "core/math/point.h"
#include "core/texture.h"

#include <optional>

enum class TetraminoType
{
    Z,
    L,
    O,
    S,
    I,
    J,
    T,

    Count
};

using TetraminoDef = Matrix<bool, 4>;

class Tetramino
{
public:
    Tetramino(App& app, const Point& pos, float speed, TetraminoType type)
        : m_def(FromType(type))
        , m_cell(app.Assets->GetTexture("images/block.png", {CellSize, CellSize}), Colors::Red)
        , m_pos(pos)
        , m_speed(speed)
    {
    }

    void Update(App& app);
    void Draw(App& app);

    const TetraminoDef& GetTetraminoDef() const
    {
        return m_def;
    }

private:
    static const TetraminoDef& FromType(TetraminoType type);

    TetraminoDef m_def{};
    Cell m_cell;

    Point m_pos{};
    FPoint m_pos_accumulator{};

    float m_move_horizontal_delta_accum{};
    float m_speed{};
    float m_horizontal_speed{0.05f/ m_speed};

    static constexpr size_t CellSize = 32;
};