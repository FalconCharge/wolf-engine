#include "core/SceneView.h"
#include "core/SceneManager.h"

namespace wolf
{
    void SceneView::Init()
    {
        std::cout << "Scene View Initialized!\n";
    }
    // Render all the objects inside of gameObjectManager
    void SceneView::Render(int width, int height)
    {
        m_GameObjectManager.Render();
    }

    // Skip the updates | Updates happen when the game is in play mode (GameScene.h)
    void SceneView::Update(float dt)
    {
        return;
    }

}