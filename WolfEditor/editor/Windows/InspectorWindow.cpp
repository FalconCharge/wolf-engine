#include "InspectorWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>

#include <glm/gtc/matrix_transform.hpp>


InspectorWindow::InspectorWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected)
    : ImguiWindow("Inspector"),
     m_gameObjects(gameObjects), m_selectedIndex(selected)
{}

void InspectorWindow::WindowSetup()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 viewportPos = viewport->Pos;   // top-left corner
    ImVec2 viewportSize = viewport->Size; // width and height

    // RIGHT: Inspector
    float margin = 10.0f;       // margin from the edge
    float inspectorWidth = 350; // fixed width for the panel
    ImVec2 inspectorPos = ImVec2(viewportPos.x + viewportSize.x - inspectorWidth - margin, viewportPos.y + 33);
    ImVec2 inspectorSize = ImVec2(inspectorWidth, viewportSize.y - 300 - margin); // height minus top and bottom margins

    //ImGui::SetNextWindowPos(inspectorPos, ImGuiCond_Once);
    //ImGui::SetNextWindowSize(inspectorSize, ImGuiCond_Once);
}

void InspectorWindow::DrawContent()
{
    // Placement
    ImVec2 viewport_pos = ImGui::GetMainViewport()->Pos;
    ImVec2 viewport_size = ImGui::GetMainViewport()->Size;
    float margin = 10.0f;
    ImVec2 pos = ImVec2(viewport_pos.x + viewport_size.x - margin, viewport_pos.y + margin);

    ImGui::SetNextWindowPos(pos, ImGuiCond_Once, ImVec2(1.0f, 0.0f));

    if (m_selectedIndex >= 0 && m_selectedIndex < (int)m_gameObjects.size())
    {
        ImGui::Text("Selected GameObject:");
        ImGui::Text("%s", m_gameObjects[m_selectedIndex]->GetName().c_str());

        static char buffer[128];
        strcpy_s(buffer, m_gameObjects[m_selectedIndex]->GetName().c_str());

        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
        {
            m_gameObjects[m_selectedIndex]->SetName(buffer);
        }

        ImGui::Text("Transform");
        glm::vec3 pos = m_gameObjects[m_selectedIndex]->GetTransform().GetPosition();
        glm::vec3 rot = glm::degrees(glm::eulerAngles(m_gameObjects[m_selectedIndex]->GetTransform().GetRotation()));
        glm::vec3 scale = m_gameObjects[m_selectedIndex]->GetTransform().GetScale();

        if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) {
            m_gameObjects[m_selectedIndex]->GetTransform().SetPosition(pos);
        }
        if (ImGui::DragFloat3("Rotation", &rot.x, 0.5f)) { // Edit in degrees
            // Convert degrees back to radians
            glm::vec3 newEulerRadians = glm::radians(rot); // Convert degrees to radians

            // Convert Euler radians back to quaternion
            glm::quat newQuat = glm::quat(newEulerRadians);
            m_gameObjects[m_selectedIndex]->GetTransform().SetRotation(newQuat);
        }

        if(ImGui::DragFloat3("Scale", &scale.x, 0.1f)) {
            m_gameObjects[m_selectedIndex]->GetTransform().SetScale(scale);
        }
    }
    else
    {
        ImGui::Text("No GameObject selected");
    }
}
