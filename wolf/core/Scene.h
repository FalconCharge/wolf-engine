#pragma once

#include "core/GameObjectManager.h"
#include <vector>

namespace wolf
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void Update(float deltaTime);
        void Render();

        void AddGameObject(GameObject* gameObject);
        void RemoveGameObject(GameObject* gameObject);

    private:
        std::vector<GameObject*> m_gameObjects;
    };
}