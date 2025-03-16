#pragma once

#include "core/math/matrix.h"
#include "core/app.h"

class Board
{
public:
    static constexpr const int Width = 10;
    static constexpr const int Height = 20;
    static constexpr const int CellSize = 32;
    
    void Draw(App& app) {
        // Rect rect{0, 0, Width * CellSize, Height * CellSize};
        // app.Renderer->DrawRect(rect, Colors::White);
        DrawGrid(app);
    }
private:
    void DrawGrid(App& app) {
        for (int i = 0; i <= Height; i++) {
            Point p1{0, i * CellSize};
            Point p2{CellSize * Width, i * CellSize};
            app.Renderer->DrawLine(p1, p2, Colors::White & HalfTransparent);
        }
        for (int i = 0; i <= Width; i++) {
            Point p1{i * CellSize, 0 };
            Point p2{i * CellSize, CellSize * Height};
            app.Renderer->DrawLine(p1, p2, Colors::White & HalfTransparent);
        }
    }
    // Matrix<bool, >
    
    static constexpr const Color HalfTransparent{255, 255, 255, Colors::White.a / 2};
};