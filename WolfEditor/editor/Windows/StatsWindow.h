#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include "core/SceneManager.h"
#include <string>
#include <memory>
#include "core/EngineStats.h"


class StatsWindow : public ImguiWindow
{
    public:
        StatsWindow();

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members

        // Methods
};
