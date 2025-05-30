#pragma once

#include "pentamino.h"
#include <random>

class FigureGenerator
{
public:
    TetraminoType MakeRandFigure() {
        return (TetraminoType)m_dist(m_rd);
    }
private:
    std::random_device m_rd;
    std::uniform_int_distribution<> m_dist{(int)TetraminoType::Begin, (int)TetraminoType::End};
};