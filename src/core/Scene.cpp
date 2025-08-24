#include "core/Scene.h"

namespace wolf
{
    Scene::Scene(const std::string& name)
        : m_Name(name), m_GameObjectManager()
    {
    }


    void Scene::Update(float deltaTime)
    {
        m_GameObjectManager.Update(deltaTime);
    }

    void Scene::Render(int width, int height)
    {
        m_GameObjectManager.Render();
    }
}
