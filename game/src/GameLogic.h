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
        wolf::Engine::Instance().GetSceneManager().LoadScene<wolf::GameScene>("Test Scene");
    }

    void Update(float dt, wolf::App* app)
    {
        wolf::Engine::Instance().GetSceneManager().Update(dt);
    }

    void Render(int width, int height)
    {
        wolf::Engine::Instance().GetSceneManager().Render(width, height);
    }

private:

};
