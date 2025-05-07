#include "rect.h"

bool Contains(const Rect& rect, const Point& point)
{
    return SDL_PointInRect(&point, &rect);
}