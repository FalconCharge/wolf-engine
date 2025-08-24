#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/App.h"
#include "Imgui.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <memory>

#include "src/GameLogic.h"


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

class WolfEditor : public wolf::App{
    public: 
        WolfEditor() : wolf::App("Wolf Editor")
        {
            // SetUp ImGui
            m_Imgui = std::make_unique<Imgui>(this->getWindow());
            // The 1920 and 1080 is the quality of the image
            m_GameView = new wolf::RenderTarget(1920, 1080, wolf::Texture::FMT_8888);

            m_Imgui->Init(wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager(), m_GameView);
                        
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();
            m_game.Update(dt, this);
        }

        void Render() override
        {
            // Editor-specific rendering logic goes here
            glfwPollEvents();

            m_GameView->Bind();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set to dark gray
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear with that color

            // Game Scene rendering
            m_game.Render(m_width, m_height);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            m_Imgui->Render();
        }



    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;

        wolf::RenderTarget* m_GameView;

        // The game Src code
        GameLogic m_game;

};

int main(int, char**)
{
    WolfEditor editor;
    editor.Run();
    return 0;
}
