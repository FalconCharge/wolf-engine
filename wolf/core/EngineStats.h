#pragma once

struct EngineStats {
    float FPS = 0.0f;
    int drawCalls = 0;
    int entities = 0;

    // Singleton accessor
    static EngineStats& Get() {
        static EngineStats instance; // created on first use, guaranteed single instance
        return instance;
    }

    // Optional: delete copy/move constructors to enforce singleton
    EngineStats(const EngineStats&) = delete;
    EngineStats& operator=(const EngineStats&) = delete;
    EngineStats(EngineStats&&) = delete;
    EngineStats& operator=(EngineStats&&) = delete;

private:
    EngineStats() = default; // private constructor
};
