#pragma once
#include "core/Scene.h"
#include <iostream>
#include "render/Model.h"

namespace wolf
{

    class SceneView : public Scene
    {
    public:
        SceneView(const std::string& name) : Scene(name) {}

        void Init() override;

        void Update(float dt) override;

        void Render(int width, int height);

        void ShutDown() override
        {
            std::cout << "TestScene Shutting down: Doesn't do anything rn\n";
        }
    private:
        Model* m_testModel = nullptr;
    };
}