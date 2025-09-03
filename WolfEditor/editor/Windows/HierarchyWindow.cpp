#include "HierarchyWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "core/SceneManager.h"

#include "InspectorWindow.h"

#include "objects/debugCube.h"

HierarchyWindow::HierarchyWindow(int selected) : ImguiWindow("Hierarchy"), m_selectedIndex(selected)
{

}
void HierarchyWindow::WindowSetup(){
    // If we want to setup the window in a certain way change some shit here
}
void HierarchyWindow::DrawContent()
{
    auto gameObjectManager = wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager();

    // Right-click anywhere in the Hierarchy window
    if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight))
    {
        if (ImGui::MenuItem("Create Empty GameObject"))
        {
            wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager()->CreateGameObject<DebugCube>();
            
        }
        ImGui::EndPopup();
    }

    for (size_t i = 0; i < gameObjectManager->GetGameObjects().size(); ++i)
    {
        wolf::GameObject* go = gameObjectManager->GetGameObjects()[i].get();
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
    // Right clikc context menu for this node
    if(ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete GameObject"))
        {
            auto gameObjectManager = wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager();
            gameObjectManager->DestroyGameObject(go);
            if (m_selectedIndex == index)
            {
                m_selectedIndex = -1; // Deselect if the selected object is deleted
                if (m_inspectorWindow) {
                    if (auto inspector = dynamic_cast<InspectorWindow*>(m_inspectorWindow))
                    {
                        inspector->SetSelectedGameObject(-1);
                    }
                }
            }
        }
        ImGui::EndPopup();
    }
    if (opened)
    {
        for (wolf::Transform* child : go->GetTransform().GetChildren())
        {
            // Find the GameObject that owns this Transform
            wolf::GameObject* childGO = child->GetOwner();

            auto gameObjectManager = wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager();


            int childIndex = -1;
            for (size_t i = 0; i < gameObjectManager->GetGameObjects().size(); ++i)
            {
                if (gameObjectManager->GetGameObjects()[i].get() == childGO)
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

