#include "InspectorWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>


InspectorWindow::InspectorWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected)
    : ImguiWindow("Inspector"), m_gameObjects(gameObjects), m_selectedIndex(selected)
{}

void InspectorWindow::DrawContent()
{
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
    }
    else
    {
        ImGui::Text("No GameObject selected");
    }
}
