#include "scene.h"

void Scene::AddChild(SceneObjectPtr obj, int depth)
{
    m_objects.emplace_back(std::move(obj));
}

void Scene::Update()
{
    for (auto& o : m_childs)
    {
        o->Update();
    }
}

void Scene::Draw(Renderer* renderer)
{
    for (auto& o : m_childs)
    {
        o->Draw();
    }
}