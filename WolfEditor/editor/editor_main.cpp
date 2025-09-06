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
            m_SceneView = new wolf::RenderTarget(1920, 1080, wolf::Texture::FMT_8888);

            // Create the editor scene
            m_EditorScene = std::make_unique<wolf::EditorScene>();
            m_EditorScene->Init();

            m_Imgui->Init(m_GameView, m_SceneView);

            wolf::Engine::Instance().GetSceneManager().SetActiveScene(m_EditorScene->GetGameScene());
                        
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();

            if(wolf::Engine::Instance().IsPlaying()){
                m_EditorScene->GetGameScene()->Update(dt);
            }

            m_EditorScene->GetEditorCamera()->update(dt);

        }

        // Note that if we want to render specifc thing in the editor we do it here EX: Grid or Gizmos
        void Render() override
        {
            // Editor-specific rendering logic goes here
            glfwPollEvents();


            // Game view rendering
            m_GameView->Bind();
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set to dark gray
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear with that color

            // Render using the game camera
            m_EditorScene->GetGameScene()->Render(
                m_EditorScene->GetGameScene()->GetMainCamera()->GetViewMatrix(),
                m_EditorScene->GetGameScene()->GetMainCamera()->GetProjMatrix()
            );

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // Render using the Scene view Camera
            m_SceneView->Bind();
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_EditorScene->RenderSceneView(); // editor camera renders scene

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // --- UI ---
            m_Imgui->Render();

        }



    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;

        wolf::RenderTarget* m_GameView;
        wolf::RenderTarget* m_SceneView;

        // The game Src code
        GameLogic m_game;

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
