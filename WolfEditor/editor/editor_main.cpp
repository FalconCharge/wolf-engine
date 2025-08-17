#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/App.h"
#include "Imgui.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <memory>

#include "examplemain.h"

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
            m_GameView = new wolf::RenderTarget(1280, 720, wolf::Texture::FMT_8888);

            m_Imgui->Init(&m_gameObjectManager, m_GameView); // TODO Pass the FBO


            // Setup the game files
            // m_week2 = Week2();
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();
            //m_week2.Update(dt);
        }

        void Render() override
        {
            // Editor-specific rendering logic goes here

            glfwPollEvents();

            m_GameView->Bind();
            
            // Render
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            m_Imgui->Render();
            
            //m_week2.Render();

        }

    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;
        wolf::GameObjectManager m_gameObjectManager;

        wolf::RenderTarget* m_GameView;

        // The game Src code
        //Week2 m_week2;

};

int main(int, char**)
{
    WolfEditor editor;
    editor.Run();
    return 0;
}
