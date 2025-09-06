#include "core/camera.h"

#include "editorScene.h"

#include <iostream>

namespace wolf
{
    EditorScene::EditorScene(){
        m_GameScene = std::make_unique<GameScene>("Game Scene");
    }

    EditorScene::~EditorScene(){
        std::cout << "Shutting down the editor Scene" << std::endl;
    }

    void EditorScene::Init()
    {
        std::cout << "Editor Scene Initialized!\n";
        m_GameScene->Init();
        m_EditorCamera = std::make_shared<EditorCamera>(
            45.0f, 16.0f/9.0f, 0.1f, 1000.0f
        );
    }

    void EditorScene::Update(float dt){
        if(wolf::Engine::Instance().IsPlaying()){
            m_GameScene->Update(dt);
        }

        m_EditorCamera->update(dt);
    }

    void EditorScene::RenderSceneView()
    {
        m_GameScene->Render(m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetProjMatrix());
    }

    void EditorScene::RenderGameView()
    {
        // Renders game objects with the game’s main camera
        m_GameScene->Render(
                m_GameScene->GetMainCamera()->GetViewMatrix(),
                m_GameScene->GetMainCamera()->GetProjMatrix()
            );
    }

}