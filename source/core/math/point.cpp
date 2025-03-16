#include "point.h"

Point SubPoint(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

Point AddPoint(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

Point RotatedPoint(const Point& center, float angle_rad, const Point& p)
{
    float s = sin(angle_rad);
    float c = cos(angle_rad);

    // translate point back to origin:
    const auto origin = SubPoint(p, center);

    // rotate point
    const Point rotated = {
        static_cast<int>(origin.x * c - origin.y * s),
        static_cast<int>(origin.x * s + origin.y * c)
    };

    // translate point back:
    return AddPoint(rotated, center);
}