// ------------------------------------------------------------
// Class: EditorScene
// Brief: EditorScene is used to render when we are running the editor
//          We Render 2 scenes the game view and scene view
//          A useful feature to add would be stopping the render process when the windows are closed or a single window is closed
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
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