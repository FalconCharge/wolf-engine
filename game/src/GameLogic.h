#pragma once
#include <stdio.h>
#include <iostream>
#include "wolf.h"


#include "core/GameObjectManager.h"
#include "core/SceneManager.h"  

class GameLogic
{
public:
    GameLogic()
    {
        wolf::SceneManager::Instance().LoadScene<wolf::GameScene>("Test Scene");
    }

    void Update(float dt, wolf::App* app)
    {
        wolf::SceneManager::Instance().Update(dt);
    }

    void Render(int width, int height)
    {
        wolf::SceneManager::Instance().Render(width, height);
    }

private:

};
