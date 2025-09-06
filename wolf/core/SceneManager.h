/*
//  A Singleton for managing scenes
*/
#pragma once
#include <memory>
#include "GameScene.h"


#include <fstream>
namespace wolf{
    class SceneManager {

    public:
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

        void SaveActiveScene(const std::string& filepath){
            std::cout << "Saving Scene to file: " << filepath << "\n";
            std::string path = "wolf/scenes/" + filepath;
            if (m_CurrentScene) {
                YAML::Node sceneNode = m_CurrentScene->Serialize();
                std::ofstream fout(path);
                fout << sceneNode;
            }
        }

        void LoadSceneFromFile(const std::string& filepath){
            std::cout << "Loading Scene from file: " << filepath << "\n";
            std::string path = "wolf/scenes/" + filepath;
            if (m_CurrentScene) {
                m_CurrentScene->ShutDown();
            }
            m_CurrentScene = std::make_unique<GameScene>("LoadedScene");
            std::ifstream fin(path);
            YAML::Node sceneNode = YAML::Load(fin);
            m_CurrentScene->Deserialize(sceneNode);
            m_CurrentScene->Init();
        }

    private:
        std::unique_ptr<Scene> m_CurrentScene;

    };

}
