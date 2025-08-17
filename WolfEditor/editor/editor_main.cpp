#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/App.h"
#include "Imgui.h"
#include "core/GameObjectManager.h"
#include <memory>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

class WolfEditor : public wolf::App{
    public: 
        WolfEditor() : wolf::App("Wolf Editor"), m_gameObjectManager()
        {
            // SetUp ImGui
            m_Imgui = std::make_unique<Imgui>(this->getWindow());
            m_Imgui->Init(&m_gameObjectManager);

            m_gameObjectManager.CreateGameObject()->SetName("Test1");
            m_gameObjectManager.CreateGameObject()->SetName("Test2");
            m_gameObjectManager.CreateGameObject()->SetName("Test3");

            wolf::GameObject* go1 = m_gameObjectManager.FindGameObjectByName("Test1");
            wolf::GameObject* go2 = m_gameObjectManager.FindGameObjectByName("Test2");

            go2->SetParent(go1);
            go1->GetTransform().SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
            //go1->GetTransform().DebugString();
            //go2->GetTransform().DebugString();

        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();
        }

        void Render() override
        {
            // Editor-specific rendering logic goes here

            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_Imgui->Render();
        }

    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;
        wolf::GameObjectManager m_gameObjectManager;
        

};

int main(int, char**)
{
    WolfEditor editor;
    editor.Run();
    return 0;
}
