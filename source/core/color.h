#pragma once

#include <SDL_pixels.h>

using Color = SDL_Color;

namespace Colors
{
constexpr const Color Transparent = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
constexpr const Color Opaque = { 0, 0, 0, SDL_ALPHA_OPAQUE };

constexpr const Color RED = {255, 0, 0, 255};        // Red
constexpr const Color GREEN = {0, 255, 0, 255};      // Green
constexpr const Color BLUE = {0, 0, 255, 255};       // Blue
constexpr const Color WHITE = {255, 255, 255, 255};  // White
constexpr const Color BLACK = {0, 0, 0, 255};        // Black
constexpr const Color YELLOW = {255, 255, 0, 255};   // Yellow
constexpr const Color CYAN = {0, 255, 255, 255};     // Cyan
constexpr const Color MAGENTA = {255, 0, 255, 255};  // Magenta
constexpr const Color GRAY = {128, 128, 128, 255};   // Gray
constexpr const Color ORANGE = {255, 165, 0, 255};   // Orange
constexpr const Color PURPLE = {128, 0, 128, 255};   // Purple
constexpr const Color BROWN = {165, 42, 42, 255};     // Brown
constexpr const Color PINK = {255, 192, 203, 255};   // Pink
constexpr const Color LIGHT_GRAY = {211, 211, 211, 255}; // Light Gray
constexpr const Color DARK_GRAY = {169, 169, 169, 255}; // Dark Gray

} // namespace Colors

constexpr Color operator|(const Color& l, const Color& r)
{
    return Color { static_cast<Uint8>(l.r | r.r), static_cast<Uint8>(l.g | r.g), static_cast<Uint8>(l.b | r.b), static_cast<Uint8>(l.a | r.a) };
}

constexpr Color operator&(const Color& l, const Color& r)
{
    return Color { static_cast<Uint8>(l.r & r.r), static_cast<Uint8>(l.g & r.g), static_cast<Uint8>(l.b & r.b), static_cast<Uint8>(l.a & r.a) };
}