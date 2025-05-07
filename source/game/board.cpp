#include "board.h"

#include "constant.h"
#include "core/color.h"
#include "core/math/point.h"
#include "game_app.h"
#include "grid.h"

#include <cstddef>
#include <optional>

Board::Board(GameApp& app)
    : m_app { app }
{
    m_current = MakeFigure();
    m_current->SetOffset({BoardPositionX , BoardPositionY });
    m_current->SetPos({ FigureStartPosX, FigureStartPosY });

    m_next = MakeFigure();
    m_next->SetOffset({PreviewFigurePositionX , PreviewFigurePositionY });

    m_font.Load("fonts/minogram_6x10.xml");
    m_font.SetScale(2.0f);
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
            if (auto r = FindFilledRows(); !r.empty())
            {
                m_delete_row_anim = MakeDeleteColorAnimation(std::move(r));
            }
        }
    }

    if (m_delete_row_anim) m_delete_row_anim();
}

void Board::Draw(GameApp& app)
{
    DrawGrid(app);
    DrawCells(app);

    const auto size = m_font.CalcTextSize("Next figure");
    auto center_x = PreviewFigurePositionX + (4 * CellSize / 2);
    Point pos{center_x - size.x / 2, PreviewFigurePositionY - size.y * 3};
    m_font.Draw(pos, "Next figure");

    m_current->Draw(app);
    m_next->Draw(app);

    pos = {PreviewFigurePositionX, PreviewFigurePositionY + (5 * CellSize)};
    m_font.Draw(pos, "Score: %d", m_score);
    pos.y += size.y * 2;
    m_font.Draw(pos, "Level: %d", m_level);
    pos.y += size.y * 2;
    m_font.Draw(pos, "Lines: %d", m_removed_rows);
}

void Board::DrawGrid(GameApp& app)
{
    ::DrawGrid(app.Renderer, {BoardPositionX, BoardPositionY}, {Width, Height}, {CellSize, CellSize}, Colors::WHITE & HalfTransparent);
    ::DrawGrid(app.Renderer, {PreviewFigurePositionX, PreviewFigurePositionY}, {4, 4}, {CellSize, CellSize}, Colors::WHITE & HalfTransparent);
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
            pos.x = BoardPositionX + CellSize * c;
            pos.y = BoardPositionY + CellSize * r;

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
    m_current = m_next;
    m_current->SetOffset({BoardPositionX , BoardPositionY });
    m_current->SetPos({ FigureStartPosX, FigureStartPosY });

    m_next = MakeFigure();
    m_next->SetOffset({PreviewFigurePositionX , PreviewFigurePositionY });
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

void Board::DeleteRows(std::vector<size_t> rows)
{
    m_removed_rows += rows.size();
    for (size_t r : rows)
    {
        DeleteRow(r);
    }

    if (m_removed_rows % 10 == 0)
    {
        m_level += 1;
    }
}

std::vector<size_t> Board::FindFilledRows() const
{
    std::vector<size_t> result;
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
            result.emplace_back(r);
        }
    }
    return result;
}

std::function<void()> Board::MakeDeleteColorAnimation(std::vector<size_t> rows)
{
    return [this, rows = std::move(rows), alfa = (int)Colors::Opaque.a]() mutable
    {
        alfa -= 5;
        for (size_t r : rows)
        {
            for (size_t c = 0; c < m_board_matrix.GetCols(); c++)
            {
                auto& v = m_board_matrix[r][c];
                if (v)
                    v->Color().a = alfa;
            }
        }

        if (alfa <= 0)
        {
            DeleteRows(std::move(rows));
            m_delete_row_anim = nullptr;
        }
    };
}

Tetramino* Board::MakeFigure()
{
    const auto type = m_figure_gen.MakeRandFigure();
    return new Tetramino(this, m_app, {}, m_current_speed + (m_level * 0.1f), type);
}
