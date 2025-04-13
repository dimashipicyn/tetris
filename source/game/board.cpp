#include "board.h"

#include "core/color.h"
#include "core/math/point.h"
#include "game_app.h"
#include <cstddef>
#include <optional>

Board::Board(GameApp& app)
    : m_app { app }
{
    m_current = m_figure_gen.MakeRandFigure(app, { 0, 0 }, 2.5f);
}

void Board::Update(GameApp& app)
{
    if (m_current)
    {
        m_current->Update(app);
        if (Intersect(m_current->GetPos(), m_current->GetFigure()))
        {
            m_current->SetPos(AddPoint(m_current->GetPos(), {0, -1}));
            NextFigure();
        }

        if (!m_delete_row_anim)
        {
            if (auto r = FindFilledRow(); r)
            {
                m_delete_row_anim = MakeDeleteColorAnimation(*r);
            }
        }
    }

    if (m_delete_row_anim) m_delete_row_anim();
}

void Board::Draw(GameApp& app)
{
    DrawGrid(app);
    DrawCells(app);
    if (m_current)
    {
        m_current->Draw(app);
    }
}

void Board::DrawGrid(GameApp& app)
{
    for (int i = 0; i <= Height; i++)
    {
        Point p1 { 0, i * CellSize };
        Point p2 { CellSize * Width, i * CellSize };
        app.Renderer->DrawLine(p1, p2, Colors::WHITE & HalfTransparent);
    }
    for (int i = 0; i <= Width; i++)
    {
        Point p1 { i * CellSize, 0 };
        Point p2 { i * CellSize, CellSize * Height };
        app.Renderer->DrawLine(p1, p2, Colors::WHITE & HalfTransparent);
    }
}

void Board::DrawCells(GameApp& app)
{
    for (size_t r = 0; r < m_board_matrix.GetRows(); r++)
    {
        for (size_t c = 0; c < m_board_matrix.GetCols(); c++)
        {
            auto& v = m_board_matrix.Value(r, c);
            if (!v)
                continue;

            Point pos;
            pos.x = CellSize * c;
            pos.y = CellSize * r;

            v->SetPos(pos);
            v->Draw(app);
        }
    }
}

bool Board::Intersect(const Point& pos, const Figure& figure) const
{
    for (size_t f_row = 0; f_row < figure.GetRows(); f_row++)
    {
        for (size_t f_col = 0; f_col < figure.GetCols(); f_col++)
        {
            const auto& fc = figure.Value(f_col, f_row);
            if (!fc)
            {
                continue;
            }

            const int b_col = pos.x + f_col;
            const int b_row = pos.y + f_row;
            if (b_col < 0 || b_col >= (int)m_board_matrix.GetCols())
            {
                return true;
            }

            if (b_row < 0 || b_row >= (int)m_board_matrix.GetRows())
            {
                return true;
            }

            const auto& mc = m_board_matrix.Value(b_col, b_row);
            if (mc)
            {
                return true;
            }
        }
    }
    return false;
}

void Board::NextFigure()
{
    const auto& figure = m_current->GetFigure();
    const auto& pos = m_current->GetPos();
    for (size_t f_row = 0; f_row < figure.GetRows(); f_row++)
    {
        for (size_t f_col = 0; f_col < figure.GetCols(); f_col++)
        {
            const auto& v = figure.Value(f_col, f_row);
            if (!v)
                continue;

            const int b_col = pos.x + f_col;
            const int b_row = pos.y + f_row;
            if (b_col < 0 || b_col >= (int)m_board_matrix.GetCols())
                continue;
            if (b_row < 0 || b_row >= (int)m_board_matrix.GetRows())
                continue;

            m_board_matrix[b_row][b_col] = v;
        }
    }

    delete m_current;
    m_current = m_figure_gen.MakeRandFigure(m_app, { 0, 0 }, 1.5f);
}

void Board::DeleteRow(size_t row)
{
    for (int r = row; r >= 0; r--)
    {
        for (size_t c = 0; c < m_board_matrix.GetCols(); c++)
        {
            m_board_matrix[r][c] = {};
            if (r == 0)
                continue;

            const int prev_row = r - 1;
            if (prev_row >= 0)
            {
                m_board_matrix[r][c] = m_board_matrix[prev_row][c];
            }
        }
    }
}

std::optional<size_t> Board::FindFilledRow() const
{
    for (size_t r = 0; r < m_board_matrix.GetRows(); r++)
    {
        bool filled = true;
        for (size_t c = 0; c < m_board_matrix.GetCols(); c++)
        {
            const auto& v = m_board_matrix[r][c];
            if (!v)
            {
                filled = false;
                break;
            }
        }

        if (filled)
        {
            return r;
        }
    }
    return std::nullopt;
}

std::function<void()> Board::MakeDeleteColorAnimation(size_t row)
{
    return [this, row, alfa = (int)Colors::Opaque.a]() mutable
    {
        alfa -= 5;
        for (size_t c = 0; c < m_board_matrix.GetCols(); c++)
        {
            auto& v = m_board_matrix[row][c];
            if (v)
                v->Color().a = alfa;
        }

        if (alfa <= 0)
        {
            DeleteRow(row);
            m_delete_row_anim = nullptr;
        }
    };
}
