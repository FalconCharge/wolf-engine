#include "core/Scene.h"

namespace wolf
{
    Scene::Scene(const std::string& name)
        : m_Name(name), m_GameObjectManager()
    {
    }

    Scene::~Scene()
    {
        // Cleans the scene
    }

    void Scene::Update(float deltaTime)
    {
        m_GameObjectManager.Update(deltaTime);
    }

    void Scene::Render()
    {
        m_GameObjectManager.Render();
    }
}
