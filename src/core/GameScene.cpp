#include "core/GameScene.h"
#include "core/SceneManager.h"

namespace wolf
{
    void GameScene::Init()
    {
        std::cout << "TestScene Initialized!\n";
        // Create a test cube
        // m_GameObjectManager.CreateGameObject<DebugCube>()->SetName("TestCube01");

        // m_GameObjectManager.CreateGameObject<DebugCube>()->SetParent(m_GameObjectManager.FindGameObjectByName("TestCube01"));

        //m_testModel = new Model("external/Chest.fbx");
    }
    void GameScene::Render(int width, int height)
    {
        m_GameObjectManager.Render();
        if (m_testModel)
        {
            glm::mat4 identity(1.0f);
            glm::mat4 projection = SceneManager::Instance().GetActiveScene()->GetMainCamera()->GetProjMatrix();
            glm::mat4 view = SceneManager::Instance().GetActiveScene()->GetMainCamera()->GetViewMatrix();
            if(SceneManager::Instance().GetActiveScene()->GetMainCamera() == nullptr){
                std::cout << "No main camera set for the scene! Cannot render model!\n";
                return;
            }

            m_testModel->Render(identity, view, projection);
        }
    }

    void GameScene::Update(float dt)
    {
        m_GameObjectManager.Update(dt);
    }

}