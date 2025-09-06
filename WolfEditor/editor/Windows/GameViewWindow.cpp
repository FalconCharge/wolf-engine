#include "GameViewWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "core/InputManager.h"
#include "core/SceneManager.h"

GameViewWindow::GameViewWindow(wolf::RenderTarget* m_gameView)
    : ImguiWindow("Game View"), m_gameView(m_gameView)
{
}
void GameViewWindow::WindowSetup(){
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 viewportPos = viewport->Pos;
    ImVec2 viewportSize = viewport->Size;

    float leftPanelWidth = 300.0f;   // Hierarchy
    float rightPanelWidth = 350.0f;  // Inspector
    float topBarHeight = 33.0f;
    float bottomMargin = 10.0f;

    ImVec2 gameViewPos = ImVec2(viewportPos.x + leftPanelWidth, viewportPos.y + topBarHeight);
    ImVec2 gameViewSize = ImVec2(
        viewportSize.x - leftPanelWidth - rightPanelWidth,  // width
        viewportSize.y - topBarHeight - bottomMargin       // height
    );

    //ImGui::SetNextWindowPos(gameViewPos, ImGuiCond_Once);
    //ImGui::SetNextWindowSize(gameViewSize, ImGuiCond_Once);
}


void GameViewWindow::DrawContent()
{

    // Get the available content size of the current ImGui window
    ImVec2 availSize = ImGui::GetContentRegionAvail();

    // maintain aspect ratio
    float aspect = (float)m_gameView->GetViewportWidth() / (float)m_gameView->GetViewportHeight();
    float width = availSize.x;
    float height = width / aspect;

    // If height is too tall, shrink it to fit
    if (height > availSize.y) {
        height = availSize.y;
        width = height * aspect;
    }

    ImGui::Image((ImTextureID)m_gameView->GetColorBuffer()->GetGLTexture(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

    // Hover and click detection
    bool hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
    bool clicked = wolf::InputManager::Instance().IsLMBDownRaw();

    // Lock cursor when clicked inside viewport
    if (hovered && clicked) {
        wolf::InputManager::Instance().SetCursorLocked(true);
    }

    // Unlock cursor on ESC
    if (wolf::InputManager::Instance().IsKeyJustDownRaw(GLFW_KEY_ESCAPE)) {
        wolf::InputManager::Instance().SetCursorLocked(false);
    }

    // Enable input only when cursor is locked
    wolf::InputManager::Instance().SetInputEnabled(
        wolf::InputManager::Instance().IsCursorLocked()
    );

}