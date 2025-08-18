#pragma once

#include "core/GameObjectManager.h"
#include <vector>

namespace wolf
{
    class Scene
    {
    public:
        Scene(const std::string& name);
        ~Scene();

        void Update(float deltaTime);
        void Render();


        // Getters
        GameObjectManager& GetGameObjectManager() { return m_GameObjectManager; }
        const std::string& GetName() const { return m_Name; }
        

    private:

        std::string m_Name;
        GameObjectManager m_GameObjectManager;
    };
}