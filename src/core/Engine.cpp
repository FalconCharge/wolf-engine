// Engine.cpp
#include "core/Engine.h"
#include <iostream>

namespace wolf {

    void Engine::Init() {
        std::cout << "[Engine] Initializing subsystems...\n";

        // Initialize physics
        //m_PhysicsSystem.Init();   // Does the init in consturcotr

        // Init sceneManager
        //m_SceneManager = SceneManager();

        // Later: init AudioManager, ResourceManager, Scripting, etc.

        std::cout << "[Engine] Init complete.\n";
    }

    void Engine::Shutdown() {
        std::cout << "[Engine] Shutting down subsystems...\n";


        // Need to setup a noice shutdown process But it's working 
        // AKA when I uncomment it brakes prob because app is shutting down everything
        // Destroy scenes
        //m_SceneManager.Clear();

        // Shutdown physics
        // m_PhysicsSystem.Shutdown();

        // Clear pointer to app (safety)
        m_App = nullptr;

        std::cout << "[Engine] Shutdown complete.\n";
    }
}
