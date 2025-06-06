#pragma once

#include "cell.h"
#include "core/aliases.h"
#include "core/color.h"
#include "core/font.h"
#include "core/math/matrix.h"

#include "constant.h"
#include "figure_generator.h"
#include "pentamino.h"

#include <functional>
#include <optional>

class Board
{
public:
    Board(GameApp& app);
    void Update(GameApp& app);
    void Draw(GameApp& app);
    bool Intersect(const Point& pos, const Figure& figure) const;

    bool GameOver() const;
    int Score() const;
    int Lines() const;
    int Level() const;
private:
    void DrawGrid(GameApp& app);
    void DrawCells(GameApp& app);
    void NextFigure();
    void DeleteRow(size_t row);
    void DeleteRows(std::vector<size_t> rows);
    std::vector<size_t> FindFilledRows() const;
    std::function<void()> MakeDeleteColorAnimation(std::vector<size_t> rows);
    Tetramino* MakeFigure();

    static constexpr const Color HalfTransparent { 255, 255, 255, Colors::WHITE.a / 2 };

    Matrix<std::optional<Cell>, Height, Width> m_board_matrix;

    GameApp& m_app;
    Tetramino* m_current = nullptr;
    Tetramino* m_next = nullptr;
    FigureGenerator m_figure_gen {};
    Font m_font {};

    std::function<void()> m_delete_row_anim;

    float m_current_speed { MinFigureSpeed };
    int m_removed_rows{0};
    int m_score{0};
    int m_level{1};
    bool m_game_over{};
};