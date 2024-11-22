#pragma once

#include "texture.h"

#include <map>
#include <string>

class Assets
{
public:
    Assets(Renderer* renderer)
        : m_renderer(renderer)
    {
    }
	
    Texture LoadTexture(const std::string& path, const SDL_Point& size = {});

private:
    std::string ResolvePath(const std::string& path) const;

    Renderer* m_renderer;
    std::map<std::string, Texture> m_textures {};
};