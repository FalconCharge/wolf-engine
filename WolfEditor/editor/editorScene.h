#pragma once
#include "core/GameScene.h"
#include "editorCamera.h"
#include <iostream>
#include "core/Engine.h"

namespace wolf
{

    class EditorScene
    {
    public:
        EditorScene();
        ~EditorScene();

        void Init();
        void Update(float dt);

        void RenderSceneView();
        void RenderGameView();

        GameScene* GetGameScene() { return m_GameScene.get(); }
        std::shared_ptr<Camera> GetEditorCamera() { return m_EditorCamera; }

        void ShutDown();

    private:

        std::unique_ptr<GameScene> m_GameScene;
        std::shared_ptr<EditorCamera> m_EditorCamera;


    };
}