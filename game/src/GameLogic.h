#pragma once
#include <stdio.h>
#include <iostream>
#include "wolf.h"

#include "core/GameObjectManager.h"
#include "core/Engine.h"  

class GameLogic
{
public:
    GameLogic()
    {
        wolf::Engine::Instance().GetSceneManager().LoadScene<wolf::GameScene>("Game Scene");
    }

    void Update(float dt, wolf::App* app)
    {
        wolf::Engine::Instance().GetSceneManager().Update(dt);
    }

    void Render(int width, int height)
    {
        //wolf::Engine::Instance().GetSceneManager().GetActiveScene()->Render();
    }

    void RenderGame()
    {
        // auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene();
        // auto scene = wolf::Engine::Instance().GetSceneManager().
        // scene->Render(scene->GetGameCamera()); // player/game camera
    }

    void RenderEditor(const std::shared_ptr<wolf::Camera>& editorCamera)
    {
        // auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene();
        // scene->Render(editorCamera.get()); // editor camera
    }


private:

};
