// Engine.cpp
#include "core/Engine.h"
#include <iostream>

namespace wolf {

    void Engine::Init() {
        std::cout << "[Engine] Initializing subsystems...\n";

        // Initialize physics
        //m_PhysicsSystem.Init();   // Does the init in consturcotr

        // Scene manager may not need explicit init, but you could reset it
        m_SceneManager = SceneManager();

        // Later: init AudioManager, ResourceManager, Scripting, etc.

        std::cout << "[Engine] Init complete.\n";
    }

    void Engine::Shutdown() {
        std::cout << "[Engine] Shutting down subsystems...\n";

        // Destroy scenes
        //m_SceneManager.Clear();

        // Shutdown physics
        m_PhysicsSystem.Shutdown();

        // Clear pointer to app (safety)
        m_App = nullptr;

        std::cout << "[Engine] Shutdown complete.\n";
    }
}
