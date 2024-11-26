#pragma once

#include "texture.h"
#include "aliases.h"
#include "scene_object.h"

#include <string>

class Sprite : public SceneObject
{
public:
    Sprite(const std::string& image_path, SceneObject* parent = nullptr, const Size& size = {});

    Point GetPos() const;
    void SetPos(const Point& pos);

    Size GetSize() const;
    void SetSize(const Size& size);

    void Draw(Renderer* renderer) override;
    bool HasIntersection(const Rect& rect);

private:
    Texture m_tex {};
};