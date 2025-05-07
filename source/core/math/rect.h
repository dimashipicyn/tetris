#pragma once

#include "point.h"
#include <SDL_rect.h>

using Rect = SDL_Rect;

bool Contains(const Rect& rect, const Point& point);