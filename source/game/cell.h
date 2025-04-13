#pragma once

#include "core/math/point.h"
#include "core/app.h"
#include "core/color.h"
#include "core/math/size.h"
#include "core/texture.h"

class Cell
{
public:
    // Cell() = default;
    Cell(const Texture& texture, const Color& color = Colors::WHITE)
        : m_texture(texture)
        , m_color(color)
    {}

    void SetPos(const Point& pos) {
        m_texture.Dest.x = pos.x;
        m_texture.Dest.y = pos.y;
    }

    void Draw(App& app) {
        m_texture.SetColor(m_color);
        app.Renderer->DrawTexture(m_texture);
    }

    Size GetSize() {
        return {m_texture.Dest.w, m_texture.Dest.h};
    }

    void SetColor(const Color& color) {
        m_color = color;
    }

private:
    Texture m_texture;
    Color m_color;
};