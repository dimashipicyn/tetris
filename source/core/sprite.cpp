#include "sprite.h"

#include "app.h"

Sprite::Sprite(const std::string& image_path, SceneObject* parent, const Size& size)
    : SceneObject{parent}
    , m_tex{App::Assets->GetTexture(image_path, size)}
{

}

Point Sprite::GetPos() const
{
    return {m_tex.Dest.x, m_tex.Dest.y};
}

void Sprite::SetPos(const Point& pos)
{
    m_tex.Dest.x = pos.x;
    m_tex.Dest.y = pos.y;
}

Size Sprite::GetSize() const
{
    return {m_tex.Dest.w, m_tex.Dest.h};
}

void Sprite::SetSize(const Size& size)
{
    m_tex.Dest.w = size.x;
    m_tex.Dest.h = size.y;
}

void Sprite::Draw(Renderer* renderer)
{
    m_tex.Draw(renderer);
    SceneObject::Draw(renderer);
}

bool Sprite::HasIntersection(const Rect& rect)
{
    return SDL_HasIntersection(&m_tex.Dest, &rect);
}
