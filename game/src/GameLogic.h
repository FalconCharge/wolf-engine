#pragma once
#include "wolf.h"
#include "core/GameScene.h"
#include "core/Camera.h"
#include "core/Engine.h"

class GameLogic
{
public:
    GameLogic()
    {

        auto scene = std::make_unique<wolf::GameScene>("Game Scene");
        scene->Init();

        // Give ownership to the SceneManager
        wolf::Engine::Instance().GetSceneManager().SetActiveScene(std::move(scene));

        // Create main camera (for the game view)
        m_gameCamera = std::make_unique<wolf::Camera>();

    }

    void Update(float dt)
    {
        if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
            scene->Update(dt);
    }

    void RenderGame()
    {
        if (!m_gameCamera) return;

        if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
        {
            scene->Render(
                m_gameCamera->GetViewMatrix(),
                m_gameCamera->GetProjMatrix()
            );
        }
    }

    void RenderEditor(const std::shared_ptr<wolf::Camera>& editorCamera)
    {
        if (!editorCamera) return;

        if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
        {
            scene->Render(
                editorCamera->GetViewMatrix(),
                editorCamera->GetProjMatrix()
            );
        }
    }

    wolf::Camera* GetGameCamera() { return m_gameCamera.get(); }

private:

    std::unique_ptr<wolf::Camera> m_gameCamera;
};
