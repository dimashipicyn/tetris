#pragma once

#include <SDL.h>

using Point = SDL_Point;
using FPoint = SDL_FPoint;

Point SubPoint(const Point& l, const Point& r);
Point AddPoint(const Point& l, const Point& r);
Point RotatedPoint(const Point& center, float angle_rad, const SDL_Point& p);