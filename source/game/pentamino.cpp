#include "pentamino.h"
#include "core/math/point.h"

void Pentamino::Draw(Renderer* renderer)
{
    for (const SDL_Point& p : m_def)
    {
        auto s = GetSize();
        Point t = { p.x * s.x, p.y * s.y };
        //auto r = RotatedPoint({ 5, 5 }, 90, p);
        //renderer->DrawPoint(p, { 255, 0, 0, 0 });
        //renderer->DrawPoint(r, { 0, 255, 0, 0 });
        SetPos(t);

        Sprite::Draw(renderer);
    }
}