#include "core/GameScene.h"
#include "core/SceneManager.h"

#include "core/Engine.h"
#include "core/camera.h"

namespace wolf
{
    void GameScene::Init()
    {
        std::cout << "Game Scene Initialized!\n";

        // Creating the main camera
        m_MainCamera = std::make_unique<Camera>(nullptr);

        // Set initial camera parameters
        m_MainCamera->SetPosition(glm::vec3(0.0f, 5.0f, 10.0f)); // position in world space
        m_MainCamera->SetFOV(glm::radians(60.0f));               // 60 degree FOV
        m_MainCamera->SetNear(0.1f);
        m_MainCamera->SetFar(1000.0f);
        m_MainCamera->SetAspect(16.0f / 9.0f);                  // aspect ratio
        m_MainCamera->SetSpeed(10.0f);                           // movement speed

        m_MainCamera->Init();


    }
    void GameScene::Render(glm::mat4 view, glm::mat4 proj)
    {
        m_GameObjectManager.Render(view, proj);
    }

    void GameScene::Update(float dt)
    {
        // 1. Step physics simulation
        wolf::Engine::Instance().GetPhysicsSystem().Update(dt);

        // It's currently Syncing from the physics component 
        // I didn't look too hard but something like this might be better
        // I'm guessing movement from components prob won't work 
        
        // Sync the GO's trasnform to the physics world
        //m_GameObjectManager.SyncFromPhysics();

        // 3. Run game object logic (AI, scripts, animations, etc)
        m_GameObjectManager.Update(dt);

        // Push the update changes to the physics Sim
        //m_GameObjectManager.SyncToPhysics();


        // Delete the gameObjects at the end of the frame
        m_GameObjectManager.ProcessDeletions();
    }


}