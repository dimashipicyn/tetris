#include "pentamino.h"

#include "core/input.h"
#include "core/math/point.h"
#include <SDL_scancode.h>

void Tetramino::Update(App& app)
{
    m_pos_accumulator.y += m_speed;
    if (m_pos_accumulator.y / CellSize > 0) {
        int cells = m_pos_accumulator.y / CellSize;
        m_pos.y += cells * CellSize;
        m_pos_accumulator.y = m_pos_accumulator.y - cells * CellSize;
    }

    m_move_horizontal_delta_accum += app.DeltaTime;

    if (app.Input->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        if (m_move_horizontal_delta_accum >= m_horizontal_speed) {
            m_pos.x -= CellSize;
            m_move_horizontal_delta_accum = 0;
        }
    }
    if (app.Input->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        if (m_move_horizontal_delta_accum >= m_horizontal_speed) {
            m_pos.x += CellSize;
            m_move_horizontal_delta_accum = 0;
        }
    }
    auto rotated = m_def;
    if (app.Input->IsKeyClicked(SDL_SCANCODE_UP))
    {
        rotated = m_def.Rotate(MatrixRotateDir::Left);
    }
    if (app.Input->IsKeyClicked(SDL_SCANCODE_DOWN))
    {
        rotated = m_def.Rotate(MatrixRotateDir::Right);
    }

    m_def = rotated; 
}

void Tetramino::Draw(App& app)
{
    for (size_t row = 0; row < m_def.GetRows(); row++)
    {
        for (size_t col = 0; col < m_def.GetCols(); col++)
        {
            const bool v = m_def.Value(row, col);
            if (v)
            {
                Point pos;
                pos.x = m_pos.x + CellSize * col;
                pos.y = m_pos.y + CellSize * row;

                m_cell.SetPos(pos);
                m_cell.Draw(app);
            }
        }
    }
}

const TetraminoDef& Tetramino::FromType(TetraminoType type)
{
    static TetraminoDef defs[(size_t)TetraminoType::Count] = {
        {
            false, true,  false, false,
            true,  true,  false, false,
            true,  false, false, false,
            false, false, false, false,
        },  // Z
        {
            false, true,  false, false, 
            false, true,  false, false, 
            false, true,  true,  false,
            false, false, false, false,
        },  // L
        {
            true,  true,  false, false,
            true,  true,  false, false,
            false, false, false, false,
            false, false, false, false,
        },  // O
        {
            false, true,  false, false,
            false, true,  true,  false,
            false, false, true,  false,
            false, false, false, false,

        },   // S
        {
            false, true,  false, false,
            false, true,  false, false,
            false, true,  false, false,
            false, true,  false, false,
        },  // I
        {
            false, true,  false, false,
            false, true,  false, false,
            true,  true,  false, false,
            false, false, false, false,
        },  // J
        {
            false, true,  false, false,
            true,  true,  true, false,
            false, false, false, false,
            false, false, false, false,
        }  // T
    };

    return defs[(size_t)type];
}