// TestScene.h
#pragma once
#include "core/Scene.h"
#include "GameLogic.h" // optional, if you want to use your existing logic

class TestScene : public wolf::Scene
{
public:
    TestScene(const std::string& name) : wolf::Scene(name) {}

    void Init() override
    {
        std::cout << "TestScene Initialized!\n";
        // Create a test cube
        m_GameObjectManager.CreateGameObject<DebugCube>()->SetName("TestCube01");
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
        std::cout << "TestScene Shutting down\n";
    }
};
