/*
//  A Singleton for managing scenes
*/
#pragma once
#include <memory>
#include "Scene.h"
namespace wolf{
    class SceneManager {

    public:

        static SceneManager& Instance() {
            static SceneManager instance;
            return instance;
        }

        template<typename T, typename... Args>
        void LoadScene(Args&&... args) {
            if (m_CurrentScene) {
                m_CurrentScene->ShutDown();
            }
            m_CurrentScene = std::make_unique<T>(std::forward<Args>(args)...);
            m_CurrentScene->Init();
        }

        void Update(float dt) {
            if (m_CurrentScene) m_CurrentScene->Update(dt);
        }

        void Render(int width, int height) {
            if (m_CurrentScene) m_CurrentScene->Render(width, height);
        }

        wolf::Scene* GetActiveScene() const {
            return m_CurrentScene.get();
        }

        // prevent copying
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;

    private:
        SceneManager() = default;
        std::unique_ptr<Scene> m_CurrentScene;
    };

}
