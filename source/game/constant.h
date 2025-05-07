#pragma once

constexpr const int Width = 10;
constexpr const int Height = 20;
constexpr const int CellSize = 32;

constexpr const int WindowWidth = Width * CellSize * 2;
constexpr const int WindowHeight = Height * CellSize + (2 * CellSize);
constexpr const int WindowCenterW = WindowWidth / 2;
constexpr const int WindowCenterH = WindowHeight / 2;

constexpr const int BoardPositionX = CellSize;
constexpr const int BoardPositionY = CellSize;

constexpr const int PreviewFigurePositionX = BoardPositionX + CellSize * (Width + 1);
constexpr const int PreviewFigurePositionY = CellSize;

constexpr const float MinFigureSpeed = 0.5f;
constexpr const float MaxFigureSpeed = 3.0f;
constexpr const float FigureSpeedStep = 0.25f;
constexpr const float HorizontalMoveSpeed = 30.0f;
constexpr const float DownSpeed = 15.0f;

constexpr const int FigureStartPosX = Width / 3;
constexpr const int FigureStartPosY = 0;