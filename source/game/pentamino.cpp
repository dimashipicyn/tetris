#include "pentamino.h"
#include "core/math/point.h"

void Pentamino::Update()
{
    static float y = 0;
    y += 5;
    SetPos({GetPos().x, (int)y});
}

void Pentamino::Draw(Renderer* renderer)
{
    Sprite sprite = *this;
    for (const SDL_Point& p : m_def)
    {
        auto s = GetSize();
        Point t = { p.x * s.x, p.y * s.y };
        //auto r = RotatedPoint({ 5, 5 }, 90, p);
        //renderer->DrawPoint(p, { 255, 0, 0, 0 });
        //renderer->DrawPoint(r, { 0, 255, 0, 0 });
        sprite.SetPos(AddPoint(GetPos(), t));

        sprite.Draw(renderer);
    }
}