#pragma once

#include "texture.h"
#include "aliases.h"

#include <map>
#include <string>

class App;

class Assets
{
public:
    Assets(Renderer* renderer)
        : m_renderer(renderer)
    {
    }
	
    Texture GetTexture(const std::string& path, const Size& size = {});

private:
    std::string ResolvePath(const std::string& path) const;

    Renderer* m_renderer {};
    std::map<std::string, Texture> m_textures {};
};