#pragma once

#include "texture.h"
#include "aliases.h"
#include "scene_object.h"

class Sprite : public SceneObject
{
public:
    Sprite(Texture tex, SceneObject* parent = nullptr);

    void SetPos(const Point& pos);
    void Draw(Renderer* renderer);
    bool HasIntersect(const Rect& rect);

private:
    Texture m_tex {};
};