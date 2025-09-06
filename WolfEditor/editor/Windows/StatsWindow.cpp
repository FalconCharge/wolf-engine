#include "StatsWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>

StatsWindow::StatsWindow()
    : ImguiWindow("Stats")
{
}
void StatsWindow::WindowSetup()
{

}



void StatsWindow::DrawContent()
{
    float fps = EngineStats::Get().FPS;
    int drawCalls = EngineStats::Get().drawCalls;
    int entities = EngineStats::Get().entities;
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Text("Draw Calls: %d", drawCalls);
    ImGui::Text("Entities: %d", entities);

    // Get current state
    bool physicsEnabled = wolf::SceneManager::Instance().GetActiveScene()->EnablePhysicsManager();

    // Checkbox to toggle
    if (ImGui::Checkbox("Physics System", &physicsEnabled)) {
        wolf::SceneManager::Instance().GetActiveScene()->EnablePhysicsManager(physicsEnabled);
    }
}