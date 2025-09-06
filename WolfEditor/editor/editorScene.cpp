#include "core/camera.h"

#include "editorScene.h"

#include <iostream>

namespace wolf
{
    EditorScene::EditorScene(){

    }

    EditorScene::~EditorScene(){
        std::cout << "Shutting down the editor Scene" << std::endl;
    }

    void EditorScene::Init()
    {
        std::cout << "Editor Scene Initialized!\n";

        m_EditorCamera = std::make_shared<EditorCamera>(
            45.0f, 16.0f/9.0f, 0.1f, 1000.0f
        );
    }

    void EditorScene::Update(float dt){
        if(wolf::Engine::Instance().IsPlaying()){
            if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
            {
                scene->Update(dt);
            }
        }

        m_EditorCamera->update(dt);
    }

    void EditorScene::RenderSceneView()
    {
        if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
        {
            scene->Render(m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetProjMatrix());
        }
    }

    void EditorScene::RenderGameView()
    {
        if (auto scene = wolf::Engine::Instance().GetSceneManager().GetActiveScene())
        {
            scene->Render(m_EditorCamera->GetViewMatrix(), m_EditorCamera->GetProjMatrix());
        }
    }

    void EditorScene::ShutDown(){
        
    }

}