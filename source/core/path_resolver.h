#pragma once

#include <SDL.h>
#include <string>

inline std::string ResolvePath(const std::string& path)
{
#ifdef __EMSCRIPTEN__
    return "/" + path;
#else
    return std::string(SDL_GetBasePath()) + "../assets/" + path;
#endif
}
