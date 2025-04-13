#pragma once

#include "cell.h"
#include "core/aliases.h"
#include "core/color.h"
#include "core/math/matrix.h"

#include "figure_generator.h"
#include "pentamino.h"
#include "constant.h"
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
    std::optional<size_t> FindFilledRow() const;
    
    static constexpr const Color HalfTransparent{255, 255, 255, Colors::WHITE.a / 2};

    Matrix<std::optional<Cell>, Height, Width> m_board_matrix;

    GameApp& m_app;
    Tetramino* m_current = nullptr;
    FigureGenerator m_figure_gen{};
};