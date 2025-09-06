// ------------------------------------------------------------ 
// File: EngineStats.h
// Class: EngineStats
// Brief: EngineStats is a singleton that hold engine stats
//         We use Engine stats with Imgui to display the information
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------ 
#pragma once

struct EngineStats {
    float FPS = 0.0f;
    int drawCalls = 0;  // Note Draw calls will be doubled in the editor since we are drawing the scene twice
                        // If Issues could change to only render when the window is opened
    int entities = 0;

    // Singleton accessor
    static EngineStats& Get() {
        static EngineStats instance; 
        return instance;
    }

private:
    EngineStats() = default;
};
