#include "scene.h"

SceneObject::SceneObject(SceneObject* parent)
    : m_parent{parent}
{
    if (m_parent)
    {
        m_parent->AddChild(this);
    }
}

SceneObject::~SceneObject()
{
    if (m_parent)
    {
        m_parent->RemoveChild(this);
    }

    for (auto& child : m_childs)
    {
        child->m_parent = nullptr;
        delete child;
    }
}

void SceneObject::AddChild(SceneObject* child, int /*depth*/)
{
    m_childs.emplace_back(child);
}

void SceneObject::RemoveChild(SceneObject* child)
{
    m_childs.erase(std::remove(m_childs.begin(), m_childs.end(), child), m_childs.end());
}

void SceneObject::Update()
{
    for (auto& child : m_childs)
    {
        child->Update();
    }
}

void SceneObject::Draw(Renderer* renderer)
{
    for (auto& child : m_childs)
    {
        child->Draw(renderer);
    }
}