#pragma once

#include "scene_object.h"
#include "renderer.h"

#include <vector>

class SceneObject final : public Object
{
public:
    void AddChild(SceneObjectPtr obj, int depth = 0);
    void Update() override;
    void Draw(Renderer* renderer) override;

private:
    std::vector<SceneObjectPtr> m_childs {};
};