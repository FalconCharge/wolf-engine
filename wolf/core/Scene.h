#pragma once

#include "core/GameObjectManager.h"
#include <vector>

namespace wolf
{
    class Scene
    {
    public:
        Scene(const std::string& name);
        virtual ~Scene() = default;

        virtual void Init() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render(int width, int height) = 0;
        virtual void ShutDown() = 0;

        wolf::GameObjectManager* GetGameObjectManager() {
            return &m_GameObjectManager;
        }

    protected:
        // Managers
        GameObjectManager m_GameObjectManager;


    private:

        std::string m_Name;
    };
}