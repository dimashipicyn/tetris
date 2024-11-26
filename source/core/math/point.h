#pragma once

#include <SDL.h>

SDL_Point SubPoint(const SDL_Point& l, const SDL_Point& r);
SDL_Point AddPoint(const SDL_Point& l, const SDL_Point& r);
SDL_Point RotatedPoint(const SDL_Point& center, float angle_rad, const SDL_Point& p);