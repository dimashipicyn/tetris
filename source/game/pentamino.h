#pragma once

#include "cell.h"

#include "core/assets.h"
#include "core/math/matrix.h"
#include "core/math/point.h"

#include <optional>
#include <functional>

class GameApp;

enum class TetraminoType
{
    Begin = 0,
    
    Z = Begin,
    L,
    O,
    S,
    I,
    J,
    T,

    End = T,
    Count
};

using Figure = Matrix<std::optional<Cell>, 4>;

class Tetramino
{
public:
    Tetramino(GameApp& app, const Point& pos, float speed, TetraminoType type);

    void Update(GameApp& app);
    void Draw(GameApp& app);

    const Figure& GetFigure() const {
        return m_figure;
    }

    const Point& GetPos() const {
        return m_pos;
    }

    void SetPos(const Point& pos)
    {
        m_pos = pos;
    }

private:
    const Figure& FromType(Assets* assets, TetraminoType type);

    Figure m_figure;

    Point m_pos{};
    float m_pos_accumulator{};

    float m_move_horizontal_delta_accum{};
    float m_speed{};
    float m_horizontal_speed{0.05f / m_speed};
};