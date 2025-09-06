#pragma once

#include "core/GameObjectManager.h"
#include "core/Camera.h"
#include "physics/PhysicsSystemManager.h"
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
        virtual void Render(int width, int height) = 0;
        virtual void ShutDown() = 0;

        wolf::GameObjectManager* GetGameObjectManager(){
            return &m_GameObjectManager;
        }


        const std::string& GetName() const { return m_Name; }

        void SetMainCamera(std::shared_ptr<Camera> camera){
            m_MainCamera = std::move(camera);
        }

        std::shared_ptr<Camera> GetMainCamera() { return m_MainCamera; }

        YAML::Node Serialize() const;
        void Deserialize(const YAML::Node& node);

    protected:
        // Managers
        wolf::GameObjectManager m_GameObjectManager;
        std::shared_ptr<Camera> m_MainCamera;
        PhysicsSystemManager m_PhysicsSystem;


    private:

        std::string m_Name;
    };
}