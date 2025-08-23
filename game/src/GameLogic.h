#pragma once
#include <stdio.h>
#include <iostream>
#include "wolf.h"


#include "core/GameObjectManager.h"

#include "SampleRunner.h"
#include "sampleClipSpace.h"
#include "sampleClipSpaceColors.h"
#include "sampleOrtho.h"
#include "samplePerspective.h"
#include "sampleWorldTransform.h"
#include "sampleCube.h"

class GameLogic
{
public:
    GameLogic()
    {
        // m_sampleRunner.addSample(new SampleClipSpace(nullptr));
        // m_sampleRunner.addSample(new SampleClipSpaceColors(nullptr));
        // m_sampleRunner.addSample(new SampleOrtho(nullptr));
        // m_sampleRunner.addSample(new SamplePerspective(nullptr));
        // m_sampleRunner.addSample(new SampleWorldTransform(nullptr));
        // m_sampleRunner.addSample(new SampleCube(nullptr));


    }

    void Update(float dt, wolf::App* app)
    {
        // if(app->isKeyDown(' '))
        // {
        //     m_lastDown = true;
        // }
        // else if(m_lastDown)
        // {
        //     m_sampleRunner.nextSample();
        //     m_lastDown = false;
        // }

        // m_sampleRunner.update(dt);


        if(app->isKeyDown('C'))
        {
            m_lastDown = true;
        }
        else if(m_lastDown)
        {
            if (gameObjectManager)
            {
                wolf::GameObject* cube = gameObjectManager->CreateGameObject<DebugCube>();
                cube->SetName("DebugCube01"); // if you have a naming system
            }
            m_lastDown = false;
        }

        // Update game objects
        if (gameObjectManager)
        {
            gameObjectManager->Update(dt);
        }
    }

    void Render(int width, int height)
    {
        //m_sampleRunner.render(width, height);
        gameObjectManager->Render();
    }

    void SetGameObjectManager(wolf::GameObjectManager* gameManager)
    {
        gameObjectManager = gameManager;
    }

private:
    //SampleRunner m_sampleRunner;
    bool m_lastDown = false;

    wolf::GameObjectManager* gameObjectManager = nullptr;
};
