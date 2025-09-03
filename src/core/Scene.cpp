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
        std::cout << "Scene Update: " << m_Name << " with " 
                  << m_GameObjectManager.GetGameObjects().size() << " GameObjects.\n";
    }

    void Scene::Render(int width, int height)
    {
        m_GameObjectManager.Render();
    }

    YAML::Node Scene::Serialize() const {
        YAML::Node node;
        node["Name"] = m_Name;
        node["GameObjects"] = m_GameObjectManager.Serialize();
        return node;
    }

    void Scene::Deserialize(const YAML::Node& node) {
        if (node["Name"]) {
            m_Name = node["Name"].as<std::string>();
        }
        if (node["GameObjects"]) {
            m_GameObjectManager.Deserialize(node["GameObjects"]);
        }
    }
}
