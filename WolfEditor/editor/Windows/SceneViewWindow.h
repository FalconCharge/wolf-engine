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
