/*
//  This is the Main Engine Singleton where we get all of our information
//  Mainly things like managers
*/


// Engine.h
#pragma once
#include "core/SceneManager.h"
#include "physics/PhysicsSystemManager.h"
#include "core/App.h"

namespace wolf {
    class Engine {
    public:
        static Engine& Instance() {
            static Engine instance;
            return instance;
        }

        void Init();
        void Shutdown();

        SceneManager& GetSceneManager() { return m_SceneManager; }
        PhysicsSystemManager& GetPhysicsSystem() { return m_PhysicsSystem; }
        
        App* GetApp() { return m_App; }
        void SetApp(App* app) { m_App = app; }

        bool IsPlaying() const { return m_IsPlaying; }
        void SetPlaying(bool playing) { m_IsPlaying = playing; }

    private:
        Engine() = default;
        ~Engine() = default;

        App* m_App = nullptr;

        SceneManager m_SceneManager;
        PhysicsSystemManager m_PhysicsSystem;

        bool m_IsPlaying = false;
    };
}
