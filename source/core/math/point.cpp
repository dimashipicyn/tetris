#include "point.h"

SDL_Point SubPoint(const SDL_Point& l, const SDL_Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

SDL_Point AddPoint(const SDL_Point& l, const SDL_Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

SDL_Point RotatedPoint(const SDL_Point& center, float angle_rad, const SDL_Point& p)
{
    float s = sin(angle_rad);
    float c = cos(angle_rad);

    // translate point back to origin:
    const auto origin = SubPoint(p, center);

    // rotate point
    const SDL_Point rotated = {
        static_cast<int>(origin.x * c - origin.y * s),
        static_cast<int>(origin.x * s + origin.y * c)
    };

    // translate point back:
    return AddPoint(rotated, center);
}