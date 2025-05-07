#include "pentamino.h"

#include "board.h"
#include "core/color.h"
#include "core/input.h"
#include "core/math/point.h"

#include "constant.h"
#include "game/game_app.h"
#include "core/math/easing.h"

#include <SDL_scancode.h>

Tetramino::Tetramino(Board* board, GameApp& app, const Point& pos, float speed, TetraminoType type)
    : m_board(board)
    , m_figure(FromType(app.Assets, type))
    , m_pos(pos)
    , m_speed(speed)
{
}

void Tetramino::Update(GameApp& app)
{
    Point new_pos = m_pos;

    float speed = m_horizontal_speed;
    if (app.Input->IsKeyClicked(SDL_SCANCODE_LEFT))
    {
        new_pos.x -= 1;
    }
    else if (app.Input->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        speed = ease_apply(m_horizontal_speed, HorizontalMoveSpeed, &m_move_horizontal_current_time, 0.5f, app.DeltaTime, ease_in_cubic);
        if (m_move_horizontal_delta_accum >= CellSize)
        {
            new_pos.x -= 1;
            m_move_horizontal_delta_accum -= CellSize;
        }
    }
    else if (app.Input->IsKeyClicked(SDL_SCANCODE_RIGHT))
    {
        new_pos.x += 1;
    }
    else if (app.Input->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        speed = ease_apply(m_horizontal_speed, HorizontalMoveSpeed, &m_move_horizontal_current_time, 0.5f, app.DeltaTime, ease_in_cubic);
        if (m_move_horizontal_delta_accum >= CellSize)
        {
            new_pos.x += 1;
            m_move_horizontal_delta_accum -= CellSize;
        }
    }
    else
    {
        m_move_horizontal_current_time = 0;
    }

    m_move_horizontal_delta_accum += speed;

    auto rotated = m_figure;
    if (app.Input->IsKeyClicked(SDL_SCANCODE_UP))
    {
        rotated = m_figure.Rotate(MatrixRotateDir::Right);
    }

    if (!m_board->Intersect(new_pos, rotated))
    {
        m_pos = new_pos;
        m_figure = rotated;
    }

    speed = m_speed;
    if (app.Input->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        speed = ease_apply(m_speed, DownSpeed, &m_down_current_time, 0.25f, app.DeltaTime, ease_in_cubic);
    }
    else
    {
        m_down_current_time = 0;
    }

    m_pos_accumulator += speed;
    if (m_pos_accumulator >= CellSize)
    {
        m_pos.y += 1;
        m_pos_accumulator -= CellSize;
    }
}

void Tetramino::Draw(GameApp& app)
{
    for (size_t row = 0; row < m_figure.GetRows(); row++)
    {
        for (size_t col = 0; col < m_figure.GetCols(); col++)
        {
            auto v = m_figure.Value(row, col);
            if (v)
            {
                Point pos;
                pos.x = m_offset.x + m_pos.x * CellSize + CellSize * col;
                pos.y = m_offset.y + m_pos.y * CellSize + CellSize * row;

                v->SetPos(pos);
                v->Draw(app);
            }
        }
    }
}

const Figure& Tetramino::FromType(Assets* assets, TetraminoType type)
{
    Cell cell{assets->GetTexture("images/block.png", {CellSize, CellSize})};
    static Figure figures[(size_t)TetraminoType::Count] = {};
    
    static bool first = true;
    if (std::exchange(first, false)) {
        cell.Color() = Colors::RED;
        figures[(size_t)TetraminoType::Z] = {
            std::nullopt, std::nullopt, cell, std::nullopt,
            std::nullopt, cell,  cell,  std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::YELLOW;
        figures[(size_t)TetraminoType::L] = {
            std::nullopt, cell,  std::nullopt, std::nullopt, 
            std::nullopt, cell,  std::nullopt, std::nullopt, 
            std::nullopt, cell,  cell,  std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::GREEN;
        figures[(size_t)TetraminoType::O] = {
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
            std::nullopt, cell,  cell, std::nullopt,
            std::nullopt, cell,  cell,  std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::CYAN;
        figures[(size_t)TetraminoType::S] = {
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, cell,  cell,  std::nullopt,
            std::nullopt, std::nullopt, cell,  std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::PURPLE;
        figures[(size_t)TetraminoType::I] = {
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::PINK;
        figures[(size_t)TetraminoType::J] = {
            std::nullopt, std::nullopt, cell, std::nullopt,
            std::nullopt, std::nullopt, cell, std::nullopt,
            std::nullopt, cell, cell, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::BROWN;
        figures[(size_t)TetraminoType::T] = {
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
            cell,  cell,  cell, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };
    }

    return figures[(size_t)type];
}