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

        std::shared_ptr<Camera> GetEditorCamera() { return m_EditorCamera; }

        void ShutDown();

    private:

        std::shared_ptr<EditorCamera> m_EditorCamera;


    };
}