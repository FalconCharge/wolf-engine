#include "HierarchyWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>

HierarchyWindow::HierarchyWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected)
    : ImguiWindow("Hierarchy"), m_gameObjects(gameObjects), m_selectedIndex(selected)
{

}


void HierarchyWindow::DrawContent()
{
    for (int i = 0; i < (int)m_gameObjects.size(); i++)
    {
        if (ImGui::Selectable(m_gameObjects[i]->GetName().c_str(), m_selectedIndex == i))
        {
            m_selectedIndex = i;
        }
    }
}
