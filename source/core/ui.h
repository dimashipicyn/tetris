#pragma once

#include "core/color.h"
#include "font.h"
#include "math/point.h"
#include "math/rect.h"

class Ui
{
public:
    const Font& GetFont() const;
    void SetFont(Font font);

    void Active(bool active);
    void Label(const Point& pos, const char* text);
    bool Button(const Point& pos, const char* text);

private:
    void Reset();
    Color CalcColor(const Color& color, bool pressed, bool howered, bool active);
    Font m_font {};
    bool m_active { true };
};