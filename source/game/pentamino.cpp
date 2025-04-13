#include "pentamino.h"

#include "board.h"
#include "core/color.h"
#include "core/input.h"
#include "core/math/point.h"

#include "constant.h"
#include "game/game_app.h"

#include <SDL_scancode.h>

Tetramino::Tetramino(GameApp& app, const Point& pos, float speed, TetraminoType type)
    : m_figure(FromType(app.Assets, type))
    , m_pos(pos)
    , m_speed(speed)
{
}

void Tetramino::Update(GameApp& app)
{
    m_move_horizontal_delta_accum += app.DeltaTime;

    Point new_pos = m_pos;
    if (app.Input->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        if (m_move_horizontal_delta_accum >= m_horizontal_speed) {
            new_pos.x -= 1;
            m_move_horizontal_delta_accum = 0;
        }
    }
    if (app.Input->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        if (m_move_horizontal_delta_accum >= m_horizontal_speed) {
            new_pos.x += 1;
            m_move_horizontal_delta_accum = 0;
        }
    }

    auto rotated = m_figure;
    if (app.Input->IsKeyClicked(SDL_SCANCODE_UP))
    {
        rotated = m_figure.Rotate(MatrixRotateDir::Left);
    }
    if (app.Input->IsKeyClicked(SDL_SCANCODE_DOWN))
    {
        rotated = m_figure.Rotate(MatrixRotateDir::Right);
    }

    Board* board = app.board;
    if (!board->Intersect(new_pos, rotated))
    {
        m_pos = new_pos;
        m_figure = rotated;
    }

    m_pos_accumulator += m_speed;
    if (m_pos_accumulator >= CellSize) {
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
                pos.x = m_pos.x * CellSize + CellSize * col;
                pos.y = m_pos.y * CellSize + CellSize * row;

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
            std::nullopt, cell,  std::nullopt, std::nullopt,
            cell,  cell,  std::nullopt, std::nullopt,
            cell,  std::nullopt, std::nullopt, std::nullopt,
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
            std::nullopt, cell,  std::nullopt, std::nullopt,
            std::nullopt, cell,  std::nullopt, std::nullopt,
            cell,  cell,  std::nullopt, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };

        cell.Color() = Colors::BROWN;
        figures[(size_t)TetraminoType::T] = {
            std::nullopt, cell,  std::nullopt, std::nullopt,
            cell,  cell,  cell, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        };
    }

    return figures[(size_t)type];
}