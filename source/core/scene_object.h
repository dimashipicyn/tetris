#pragma once

#include "renderer.h"

#include <vector>

class SceneObject
{
public:
    SceneObject(SceneObject* parent = nullptr);
    virtual ~SceneObject();
    
    void AddChild(SceneObject* obj, int depth = 0);
    void RemoveChild(SceneObject* obj);

    virtual void Update();
    virtual void Draw(Renderer* renderer);

private:
    std::vector<SceneObject*> m_childs {};
    SceneObject* m_parent {};
};
