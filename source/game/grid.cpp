#include "grid.h"

void DrawGrid(Renderer* renderer, const Point& start, const Size& cells, const Size& cell_size, const Color& color)
{
    for (int i = 0; i <= cells.y; i++)
    {
        Point p1 { start.x, start.y + i * cell_size.y };
        Point p2 { start.x + cell_size.x * cells.x, start.y + i * cell_size.y };
        renderer->DrawLine(p1, p2, color);
    }
    for (int i = 0; i <= cells.x; i++)
    {
        Point p1 { start.x + i * cell_size.x, start.y };
        Point p2 { start.x + i * cell_size.x, start.y + cell_size.y * cells.y };
        renderer->DrawLine(p1, p2, color);
    }
}