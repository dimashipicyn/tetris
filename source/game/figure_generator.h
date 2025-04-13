#pragma once

#include "pentamino.h"
#include <random>

class FigureGenerator
{
public:
    Tetramino* MakeRandFigure(GameApp& app, const Point& pos, float speed) {
        TetraminoType type = (TetraminoType)m_dist(m_rd);
        return new Tetramino(app, pos, speed, type);
    }
private:
    std::random_device m_rd;
    std::uniform_int_distribution<> m_dist{(int)TetraminoType::Begin, (int)TetraminoType::End};
};