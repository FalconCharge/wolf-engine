#pragma once

struct EngineStats {
    float FPS = 0.0f;
    int drawCalls = 0;  // Note Draw calls will be doubled in the editor since we are drawing the scene twice
                        // If Issues could change to only render when the window is opened
    int entities = 0;

    // Singleton accessor
    static EngineStats& Get() {
        static EngineStats instance; // created on first use, guaranteed single instance
        return instance;
    }

private:
    EngineStats() = default; // private constructor
};
