#include "assets.h"

#include "SDL_image.h"
#include <SDL_filesystem.h>

Texture Assets::GetTexture(const std::string& path, const Size& size)
{
    auto it = m_textures.find(path);
    if (it != m_textures.end())
    {
        return it->second;
    }

    SDL_Texture* tex_handle = IMG_LoadTexture(m_renderer->m_renderer, ResolvePath(path).c_str());
    if (!tex_handle)
    {
        SDL_Log("LoadTexture() failed: %s\n", SDL_GetError());
        return { };
    }

    Texture texture(tex_handle);
    if (size.x != 0 && size.y != 0)
    {
        texture.Dest.w = size.x;
        texture.Dest.h = size.y;
    }

    m_textures.emplace(std::make_pair(path, texture));
    return texture;
}

std::string Assets::ResolvePath(const std::string& path) const
{
    return std::string(SDL_GetBasePath()) + "../assets/" + path;
}