#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include <string>
#include <memory>


class GameViewWindow : public ImguiWindow
{
    public:
        GameViewWindow();

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members

        // Methods
};
