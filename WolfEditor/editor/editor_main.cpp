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
            m_GameView = new wolf::RenderTarget(1920, 1080, wolf::Texture::FMT_8888);

            m_Imgui->Init(&m_gameObjectManager, m_GameView);

            // Setup samples
            m_sampleRunner.addSample(new SampleClipSpace(this));
            m_sampleRunner.addSample(new SampleClipSpaceColors(this));
            m_sampleRunner.addSample(new SampleOrtho(this));
            m_sampleRunner.addSample(new SamplePerspective(this));
            m_sampleRunner.addSample(new SampleWorldTransform(this));
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();

            if(isKeyDown(' '))
            {
                m_lastDown = true;
            }
            else if(m_lastDown)
            {
                m_sampleRunner.nextSample();
                m_lastDown = false;
            }

            m_sampleRunner.update(dt);
        }

        void Render() override
        {
            // Editor-specific rendering logic goes here
            glfwPollEvents();

            m_GameView->Bind();

            // Game Scene rendering
            m_sampleRunner.render(m_width, m_height);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            m_Imgui->Render();
        }



    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;
        wolf::GameObjectManager m_gameObjectManager;

        wolf::RenderTarget* m_GameView;

        // The game Src code
        //Week2 m_week2;

        // For running the game
        SampleRunner m_sampleRunner;
        bool m_lastDown = false;

};

int main(int, char**)
{
    WolfEditor editor;
    editor.Run();
    return 0;
}
