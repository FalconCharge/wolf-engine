// ------------------------------------------------------------
// File: Scene.h
// Class: Scene
// Brief: Scene is a abstract class that holds Systems for each scene
//          Examples are GameObjectManager and the camera
// Author: Ben Harper
// Date: 2025-09-06
// 
// Note: I'm not sure about this. But Might be better to have this be a non abstract class
//          And just put the Game Scene in this instead.
//          But that would take a bit a refactoring and well it works right now
// ------------------------------------------------------------
#pragma once

#include "core/GameObjectManager.h"
#include "core/Camera.h"
#include <vector>
#include <memory>
#include <iostream>

namespace wolf
{
    class Scene
    {
    public:

        Scene(const std::string& name);
        virtual ~Scene() = default;
        
        virtual void Init() = 0;
        virtual void Update(float dt) = 0;
        // Don't need the view and proj here since we store the cameras here I think
        virtual void Render(glm::mat4 view, glm::mat4 proj) = 0;
        virtual void ShutDown() = 0;

        wolf::GameObjectManager* GetGameObjectManager(){ return &m_GameObjectManager; }

        const std::string& GetName() const { return m_Name; }

        void SetMainCamera(std::unique_ptr<Camera> camera) { m_MainCamera = std::move(camera); }
        Camera* GetMainCamera() { return m_MainCamera.get(); }

        YAML::Node Serialize() const;
        void Deserialize(const YAML::Node& node);

    protected:
        // Managers
        wolf::GameObjectManager m_GameObjectManager;
        std::unique_ptr<Camera> m_MainCamera;

    private:

        std::string m_Name;
    };
}