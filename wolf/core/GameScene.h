#pragma once
#include "core/Scene.h"
#include <iostream>

class GameScene : public wolf::Scene
{
public:
    GameScene(const std::string& name) : wolf::Scene(name) {}

    void Init() override
    {
        std::cout << "TestScene Initialized!\n";
        // Create a test cube
        // m_GameObjectManager.CreateGameObject<DebugCube>()->SetName("TestCube01");

        // m_GameObjectManager.CreateGameObject<DebugCube>()->SetParent(m_GameObjectManager.FindGameObjectByName("TestCube01"));
    }

    void Update(float dt) override
    {
        m_GameObjectManager.Update(dt);
    }

    void Render(int width, int height) override
    {
        m_GameObjectManager.Render();
    }

    void ShutDown() override
    {
        std::cout << "TestScene Shutting down: Doesn't do anything rn\n";
    }
};
