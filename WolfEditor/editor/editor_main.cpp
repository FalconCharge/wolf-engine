#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/App.h"
#include "Imgui.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <memory>
#include "editorScene.h"

#include "editorCamera.h"

#include "core/InputManager.h"

#include "src/GameLogic.h"

#include "core/Engine.h"
#include "editorScene.h"

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

            // Create render targets
            m_GameView = std::make_unique<wolf::RenderTarget>(1920, 1080, wolf::Texture::FMT_8888);
            m_SceneView = std::make_unique<wolf::RenderTarget>(1920, 1080, wolf::Texture::FMT_8888);

            m_Imgui->Init(m_GameView.get(), m_SceneView.get());

            // Init the game Logic
            m_gameLogic = std::make_unique<GameLogic>();

            // Editor Scene
            m_EditorScene = std::make_unique<wolf::EditorScene>();
            m_EditorScene->Init();
                        
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();

            if (wolf::Engine::Instance().IsPlaying())
                m_gameLogic->Update(dt);

            m_EditorScene->GetEditorCamera()->update(dt);
        }

        void Render() override
        {
            glfwPollEvents();

            // --- Game View ---
            m_GameView->Bind();
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_gameLogic->RenderGame();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // --- Editor View ---
            m_SceneView->Bind();
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_gameLogic->RenderEditor(m_EditorScene->GetEditorCamera());

            //m_EditorScene->RenderGizmos(); // any extra editor-specific visuals
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // --- UI ---
            m_Imgui->Render();
        }



    private:
        std::unique_ptr<Imgui> m_Imgui;

        std::unique_ptr<wolf::RenderTarget> m_GameView;
        std::unique_ptr<wolf::RenderTarget> m_SceneView;

        std::unique_ptr<GameLogic> m_gameLogic;
        std::unique_ptr<wolf::EditorScene> m_EditorScene;


};

int main(int, char**)
{

    // Init engine SubSystems such as the Physics and SceneManager
    wolf::Engine::Instance().Init();
    // The Application
    WolfEditor editor;

    // Set the app for ref
    wolf::Engine::Instance().SetApp(&editor);

    // Start the Application loop
    editor.Run();
    return 0;
}
