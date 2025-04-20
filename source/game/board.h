#pragma once

#include "cell.h"
#include "core/aliases.h"
#include "core/color.h"
#include "core/math/matrix.h"

#include "figure_generator.h"
#include "pentamino.h"
#include "constant.h"
#include <functional>
#include <optional>

class Board
{
public:
    Board(GameApp& app);
    bool Intersect(const Point& pos, const Figure& figure) const;

    void Update(GameApp& app);
    void Draw(GameApp& app);
private:
    void DrawGrid(GameApp& app);
    void DrawCells(GameApp& app);
    void NextFigure();
    void DeleteRow(size_t row);
    std::vector<size_t> FindFilledRows() const;
    std::function<void()> MakeDeleteColorAnimation(std::vector<size_t> rows);
    Tetramino* MakeFigure();
    
    static constexpr const Color HalfTransparent{255, 255, 255, Colors::WHITE.a / 2};

    Matrix<std::optional<Cell>, Height, Width> m_board_matrix;

    GameApp& m_app;
    Tetramino* m_current = nullptr;
    Tetramino* m_next = nullptr;
    FigureGenerator m_figure_gen{};

    std::function<void()> m_delete_row_anim;

    float m_current_speed{MinFigureSpeed};
    // int m_removed_rows{0};
};