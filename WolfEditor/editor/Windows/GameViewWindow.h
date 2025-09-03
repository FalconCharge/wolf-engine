#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <string>
#include <memory>
#include "../editorCamera.h"


class GameViewWindow : public ImguiWindow
{
    public:
        GameViewWindow(wolf::RenderTarget* gameView, std::shared_ptr<EditorCamera> editorCamera);

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members
        wolf::RenderTarget* m_gameView;
        std::shared_ptr<EditorCamera> m_EditorCamera;
        // Methods
};
