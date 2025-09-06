// ------------------------------------------------------------ 
// Class: StatsWindow
// Brief: Used the EngineStats single to gather the values and dispaly them in a window
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------ 
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
