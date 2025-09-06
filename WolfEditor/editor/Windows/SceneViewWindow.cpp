#include "SceneViewWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "core/InputManager.h"
#include "core/Engine.h"

SceneViewWindow::SceneViewWindow(wolf::RenderTarget* m_gameView)
    : ImguiWindow("Scene View"), m_gameView(m_gameView)
{
}
void SceneViewWindow::WindowSetup(){
    // Window setup used to put the window in a certain place
}


void SceneViewWindow::DrawContent()
{


    if(ImGui::IsWindowFocused()){

        // Lock cursor on left mouse button
        if (wolf::InputManager::Instance().IsLMBDownRaw())
        {
            wolf::InputManager::Instance().SetCursorLocked(true);
        }

        // Unlock cursor on Escape
        if (wolf::InputManager::Instance().IsKeyDownRaw(GLFW_KEY_ESCAPE))
        {
            wolf::InputManager::Instance().SetCursorLocked(false);
        }

        // Enable input only when cursor is locked
        if(wolf::InputManager::Instance().IsCursorLocked()){
            wolf::InputManager::Instance().SetInputEnabled(true);
        }else{
            wolf::InputManager::Instance().SetInputEnabled(false);
        }
    }

    // Get the available content size of the current ImGui window
    ImVec2 availSize = ImGui::GetContentRegionAvail();

    // Optional: maintain aspect ratio
    float aspect = (float)m_gameView->GetViewportWidth() / (float)m_gameView->GetViewportHeight();
    float width = availSize.x;
    float height = width / aspect;

    // If height is too tall, shrink it to fit
    if (height > availSize.y) {
        height = availSize.y;
        width = height * aspect;
    }

    ImGui::Image((ImTextureID)m_gameView->GetColorBuffer()->GetGLTexture(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

}