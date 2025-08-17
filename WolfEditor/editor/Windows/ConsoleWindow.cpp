#include "ConsoleWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>

ConsoleWindow::ConsoleWindow()
    : ImguiWindow("Console")
{
}
void ConsoleWindow::WindowSetup()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 viewportPos = viewport->Pos;
    ImVec2 viewportSize = viewport->Size;

    float leftPanelWidth = 300.0f;   // Hierarchy
    float rightPanelWidth = 350.0f;  // Inspector
    float topBarHeight = 33.0f;
    float consoleHeight = 200.0f;    // How tall the console should be

    // X position starts after the left panel
    float xPos = viewportPos.x + leftPanelWidth;
    // Y position starts at the bottom of the top bar + remaining space above console
    float yPos = viewportPos.y + viewportSize.y - consoleHeight - 10.0f; // 10 px margin

    float width = viewportSize.x - leftPanelWidth - rightPanelWidth; // stretch between left and right panels
    float height = consoleHeight;

    ImVec2 consolePos = ImVec2(xPos, yPos);
    ImVec2 consoleSize = ImVec2(width, height);

    ImGui::SetNextWindowPos(consolePos, ImGuiCond_Once);
    ImGui::SetNextWindowSize(consoleSize, ImGuiCond_Once);
}



void ConsoleWindow::DrawContent()
{
    ImGui::Text("Console");

}