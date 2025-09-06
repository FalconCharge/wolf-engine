#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <string>
#include <memory>
#include "core/camera.h"


class GameViewWindow : public ImguiWindow
{
    public:
        GameViewWindow(wolf::RenderTarget* gameView);

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members
        wolf::RenderTarget* m_gameView;
        // Methods
};
