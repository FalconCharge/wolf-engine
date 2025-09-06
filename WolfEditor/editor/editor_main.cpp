#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/App.h"
#include "Imgui.h"
#include "core/GameObjectManager.h"
#include "render/RenderTarget.h"
#include <memory>
#include "Grid3D.h"

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

            m_EditorCamera = std::make_shared<EditorCamera>(
                45.0f, m_GameView->GetViewportWidth()/m_GameView->GetViewportHeight(), 0.1f, 1000.0f
            );


            m_Imgui->Init(m_GameView, m_EditorCamera);

            // We set the Main Camera for the scene to be the Editor Camera
            wolf::Engine::Instance().GetSceneManager().GetActiveScene()->SetMainCamera(m_EditorCamera);

            m_Grid = new Grid3D(10, 2.0f);

            // Init the Input Manager
            wolf::InputManager::Instance().Initialize(this->getWindow());


                        
        }

        void Update(float dt) override
        {
            m_Imgui->NewFrame();
            m_game.Update(dt, this);
            m_EditorCamera->update(dt);

            //std::cout << "Editor Camera Position: " << glm::to_string(m_EditorCamera->GetViewPosition()) << std::endl;
        }

        // Note that if we want to render specifc thing in the editor we do it here EX: Grid or Gizmos
        void Render() override
        {
            // Editor-specific rendering logic goes here
            glfwPollEvents();

            m_GameView->Bind();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set to dark gray
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear with that color

            // Game Scene rendering
            m_game.Render(m_width, m_height);   // We don't use width and height

            
            // Render the editor grid *after* the scene
            glm::mat4 view = m_EditorCamera->GetViewMatrix();
            glm::mat4 proj = m_EditorCamera->GetProjMatrix();
            //m_Grid->render(view, proj);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            m_Imgui->Render();
        }



    private:
        // Add editor-specific members here
        std::unique_ptr<Imgui> m_Imgui;

        wolf::RenderTarget* m_GameView;

        // The game Src code
        GameLogic m_game;

        Grid3D* m_Grid;

        std::shared_ptr<EditorCamera> m_EditorCamera;

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
