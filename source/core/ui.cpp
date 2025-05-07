#include "ui.h"

#include "aliases.h"
#include "color.h"
#include "input.h"
#include "provider.h"
#include "renderer.h"

const Font& Ui::GetFont() const
{
    return m_font;
}

void Ui::SetFont(Font font)
{
    m_font = font;
}

void Ui::Active(bool active)
{
    m_active = active;
}

void Ui::Label(const Point& pos, const char* text)
{
    m_font.SetColor(m_active ? Colors::WHITE : Colors::WHITE * 0.5f);
    m_font.Draw(pos, "%s", text);
    Reset();
}

bool Ui::Button(const Point& pos, const char* text)
{
    Input* i = Provider::Self().Input();
    Renderer* r = Provider::Self().Renderer();

    const Size char_size = m_font.CalcTextSize("#");
    const Size calc_size = m_font.CalcTextSize("%s", text);
    Rect calc_rect {
        pos.x,
        pos.y,
        calc_size.x + char_size.x,
        calc_size.y + char_size.y
    };

    const Point& mouse = i->MousePosition();
    const bool intersected = Contains(calc_rect, mouse);
    const bool clicked = m_active && intersected && i->IsMouseClicked(MouseButton::Left);
    const bool pressed = intersected && i->IsMouseDown(MouseButton::Left);
    const Color color = CalcColor(Colors::GREEN * 0.5f, pressed, intersected, m_active);

    if (intersected)
    {
        calc_rect.x += char_size.x;
    }
    r->DrawFillRect(calc_rect, color);

    const Point text_pos = { calc_rect.x + char_size.x / 2, calc_rect.y + char_size.y / 2 };
    m_font.SetColor(m_active ? Colors::WHITE : Colors::WHITE * 0.5f);
    m_font.Draw(text_pos, "%s", text);

    Reset();
    return clicked;
}

void Ui::Reset()
{
    m_active = true;
}

Color Ui::CalcColor(const Color& color, bool pressed, bool howered, bool active)
{
    if (!active) return color * 0.5;
    if (pressed) return color * 0.8;
    if (howered) return color * 1.2;
    return color;
}
