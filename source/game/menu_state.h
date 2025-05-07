#pragma once

#include "cell.h"
#include "constant.h"
#include "core/math/matrix.h"
#include "core/state.h"


#include <deque>
#include <random>

class MenuState : public State
{
public:
private:
    void Update(App&) override;
    void Draw(App&) override;
    void DrawUi(App& app);
    void DrawBackground(App& app);
    Point GetRandStartPos() const;

    void ProduceBackgroundCells(App& app);
    void RemoveInvisibleCells();
    void UpdateCells(float dt);

    mutable std::random_device m_rd;
    mutable std::uniform_int_distribution<> m_dist { -CellSize, WindowWidth };
    std::deque<Cell> m_cell_queue{};
    float m_produce_acc{};
    float m_move_acc{};
};