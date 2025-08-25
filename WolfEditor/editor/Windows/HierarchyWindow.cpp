#include "HierarchyWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "core/SceneManager.h"

#include "InspectorWindow.h"

#include "src/debugCube.h"

HierarchyWindow::HierarchyWindow(int selected) : ImguiWindow("Hierarchy"), m_selectedIndex(selected)
{
    m_gameObjectManager = wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager();  
}
void HierarchyWindow::WindowSetup(){
    // If we want to setup the window in a certain way change some shit here
}
void HierarchyWindow::DrawContent()
{
    // Right-click anywhere in the Hierarchy window
    if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight))
    {
        if (ImGui::MenuItem("Create Empty GameObject"))
        {
            wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager()->CreateGameObject<DebugCube>();
            
        }
        ImGui::EndPopup();
    }

    for (size_t i = 0; i < m_gameObjectManager->GetGameObjects().size(); ++i)
    {
        wolf::GameObject* go = m_gameObjectManager->GetGameObjects()[i].get();
        if (!go->GetTransform().GetParent()) // Only draw roots
        {
            DrawGameObjectNode(go, (int)i);            
        }
        
    }

}

void HierarchyWindow::DrawGameObjectNode(wolf::GameObject* go, int index)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (index == m_selectedIndex)
        flags |= ImGuiTreeNodeFlags_Selected;


    bool opened = ImGui::TreeNodeEx((void*)(intptr_t)index, flags, go->GetName().c_str());

    if (ImGui::IsItemClicked()) {
        m_selectedIndex = index;
        if (m_inspectorWindow) {
            if (auto inspector = dynamic_cast<InspectorWindow*>(m_inspectorWindow))
            {
                inspector->SetSelectedGameObject(index);
            }
        }
    }

    if (opened)
    {
        for (wolf::Transform* child : go->GetTransform().GetChildren())
        {
            // Find the GameObject that owns this Transform
            wolf::GameObject* childGO = child->GetOwner();


            int childIndex = -1;
            for (size_t i = 0; i < m_gameObjectManager->GetGameObjects().size(); ++i)
            {
                if (m_gameObjectManager->GetGameObjects()[i].get() == childGO)
                {
                    childIndex = (int)i;
                    break;
                }
            }

            DrawGameObjectNode(childGO, childIndex);
        }

        ImGui::TreePop();
    }
}

