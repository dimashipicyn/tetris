#include "pentamino.h"

void Pentamino::Draw(Renderer* renderer)
{
    for (const SDL_Point& p : m_def)
    {
        m_texture.Dest.x = p.x * m_texture.Dest.w;
        m_texture.Dest.y = p.y * m_texture.Dest.h;

        m_texture.Draw(renderer);
    }
}