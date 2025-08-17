#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include <string>
#include <memory>


class ConsoleWindow : public ImguiWindow
{
    public:
        ConsoleWindow();

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members

        // Methods
};
