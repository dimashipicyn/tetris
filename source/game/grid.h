#pragma once

#include "core/math/point.h"
#include "core/math/size.h"
#include "core/color.h"
#include "core/renderer.h"

void DrawGrid(Renderer* renderer, const Point& start, const Size& cells, const Size& cell_size, const Color& color);