#include "assets.h"

#include "SDL_image.h"

Texture Assets::LoadTexture(const std::string& path)
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
    m_textures.emplace(std::make_pair(path, texture));
    return texture;
}

std::string Assets::ResolvePath(const std::string& path) const
{
    return "../" + path;
}