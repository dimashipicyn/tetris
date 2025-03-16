#pragma once

#include <SDL_pixels.h>

using Color = SDL_Color;

namespace Colors
{
constexpr const Color White = { 255, 255, 255, SDL_ALPHA_OPAQUE };
constexpr const Color Red = { 255, 0, 0, SDL_ALPHA_OPAQUE };
constexpr const Color Green = { 0, 255, 0, SDL_ALPHA_OPAQUE };
constexpr const Color Cyan = { 0, 255, 255, SDL_ALPHA_OPAQUE };
constexpr const Color Yellow = { 255, 255, 0, SDL_ALPHA_OPAQUE };
constexpr const Color Black = { 0, 0, 0, SDL_ALPHA_OPAQUE };
constexpr const Color Transparent = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
} // namespace Colors

constexpr Color operator|(const Color& l, const Color& r)
{
    return Color { static_cast<Uint8>(l.r | r.r), static_cast<Uint8>(l.g | r.g), static_cast<Uint8>(l.b | r.b), static_cast<Uint8>(l.a | r.a) };
}

constexpr Color operator&(const Color& l, const Color& r)
{
    return Color { static_cast<Uint8>(l.r & r.r), static_cast<Uint8>(l.g & r.g), static_cast<Uint8>(l.b & r.b), static_cast<Uint8>(l.a & r.a) };
}