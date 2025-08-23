
#include "imgui.h"

#include <iostream>

#include "Windows/HierarchyWindow.h"
#include "Windows/InspectorWindow.h"
#include "Windows/GameViewWindow.h"
#include "Windows/ConsoleWindow.h"

#include "render/RenderTarget.h"

void Imgui::Init(wolf::GameObjectManager* gameObjectManager, wolf::RenderTarget* gameView)
{
    // Create ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_io = &ImGui::GetIO(); // Retrieve pointer for convenience
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // ImGui Recommends this for multi windows
    ImGuiStyle& style = ImGui::GetStyle();
    if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    //Increase the font size slightly
    ImGui::GetIO().FontGlobalScale = 1.4f;  //TODO Add a custom font for the size

    // Initialize backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core"); // GLSL version string

    // Add editor windows

    AddWindow(new GameViewWindow(gameView));

    AddWindow(new HierarchyWindow(gameObjectManager->GetGameObjects(), -1));

    AddWindow(new InspectorWindow(gameObjectManager->GetGameObjects(), -1));


    if (auto hierarchyWindow = dynamic_cast<HierarchyWindow*>(FindWindow("Hierarchy"))) {
        hierarchyWindow->SetInspectorWindow(FindWindow("Inspector"));
    }
}

void Imgui::DrawMainMenuBar(){
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f)); // x = horiz padding, y = vertical padding
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 5.0f)); // spacing between menu items
    
    if (ImGui::BeginMainMenuBar())
    {
        // Basic File Menu
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "Ctrl+N")) { /* new scene */ }
            if (ImGui::MenuItem("Open Scene...", "Ctrl+O")) { /* open */ }
            if (ImGui::MenuItem("Save Scene", "Ctrl+S")) { /* save */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { /* quit */ }
            ImGui::EndMenu();
        }
        
        // Prob will delete this
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Preferences")) {}
            ImGui::EndMenu();
        }

        // Playing game exe in editor
        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Play", "F5")) {}
            if (ImGui::MenuItem("Pause", "F6")) {}
            if (ImGui::MenuItem("Stop", "Shift+F5")) {}
            ImGui::EndMenu();
        }

        // Toggle windows on and off
        if(ImGui::BeginMenu("Windows")){
            // Toggles windows on and off
            if(ImGui::MenuItem("Hierachy")) {}
            if(ImGui::MenuItem("Inspector")) {}
            if(ImGui::MenuItem("Console")) {}
            if(ImGui::MenuItem("Game View")) {}
            ImGui::EndMenu();
        }
        
        // Tools to help with development
        if(ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Asset Importer")) {}
            if (ImGui::MenuItem("Profiler")) {}
            if (ImGui::MenuItem("Shader Editor")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Documentation")) {}
            if (ImGui::MenuItem("About")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleVar(2);
}

void Imgui::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Imgui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
}

void Imgui::Render()
{
    DrawDockSpace();

    // 2. Now render all your windows, docked into the main dockspace
    for (auto* window : m_imguiWindows)
    {
        // Draw your window content 
        window->Draw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

}

void Imgui::AddWindow(ImguiWindow* window)
{
    m_imguiWindows.push_back(window);
}

ImguiWindow* Imgui::FindWindow(const std::string& name) const
{
    for (const auto& window : m_imguiWindows)
    {
        if (name == window->GetName())
        {
            return window;
        }
    }
    return nullptr; // Not found
}

void Imgui::DrawDockSpace()
{
    // Fullscreen invisible window to hold dockspace
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar
                                  | ImGuiWindowFlags_NoCollapse
                                  | ImGuiWindowFlags_NoResize
                                  | ImGuiWindowFlags_NoMove
                                  | ImGuiWindowFlags_NoBringToFrontOnFocus
                                  | ImGuiWindowFlags_NoNavFocus
                                  | ImGuiWindowFlags_MenuBar;

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode
                                       | ImGuiDockNodeFlags_NoSplit;

    static bool dockspace_open = true;

    ImGui::Begin("DockSpaceWindow", &dockspace_open, window_flags);

    DrawMainMenuBar();

    // Create dockspace
    ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    ImGui::End();
}