#pragma once

#include "texture.h"

class Glyph
{
public:

private:
    Texture m_texture {};

    int bearingX = 0, bearingY = 0; // Offset from baseline to left/top of glyph
    int advanceX = 0, advanceY = 0; // Offset to advance to next glyph
};