// ------------------------------------------------------------
// Class: SceneViewWindow
// Brief: With the help of Imgui we render the Scene view through a render Target
//          Should always be the scene view
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <string>
#include <memory>
#include "../editorCamera.h"


class SceneViewWindow : public ImguiWindow
{
    public:
        SceneViewWindow(wolf::RenderTarget* sceneView);

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members
        wolf::RenderTarget* m_gameView;
        
        // Methods
};
