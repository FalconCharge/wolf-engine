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
            m_Imgui->Init();

            // Add editor windows
            m_Imgui->AddWindow(std::make_unique<HierarchyWindow>(
                m_gameObjectManager.GetGameObjects(), -1));

            m_Imgui->AddWindow(std::make_unique<InspectorWindow>(
                m_gameObjectManager.GetGameObjects(), -1));


            m_gameObjectManager.CreateGameObject()->SetName("GameObject 1");
            m_gameObjectManager.CreateGameObject()->SetName("GameObject 2");
            m_gameObjectManager.CreateGameObject()->SetName("GameObject 3");
          
        }

        void Update(float dt) override
        {
            // imgui always goes first
            m_Imgui->NewFrame();
        }

        void Render() override
        {
            // Editor-specific rendering logic goes here

            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



            // Render ImGui windows
            for (const auto& window : m_Imgui->GetWindows())
            {
                window->Draw();
            }

            //imgui always goes last
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
