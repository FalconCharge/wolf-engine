
#include "imgui.h"

#include <iostream>

#include "Windows/HierarchyWindow.h"
#include "Windows/InspectorWindow.h"
#include "Windows/GameViewWindow.h"
#include "Windows/StatsWindow.h"
#include "Windows/SceneViewWindow.h"

#include "render/RenderTarget.h"


#include "core/GameScene.h"
#include "core/Engine.h"

void Imgui::Init(wolf::RenderTarget* gameView, wolf::RenderTarget* sceneView)
{
    // Create ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_io = &ImGui::GetIO(); // Retrieve pointer for convenience
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // Setting up fonts
    float fontSize = 18.0f;// *2.0f;
    m_io->Fonts->AddFontFromFileTTF("WolfEditor/data/fonts/OpenSans-SemiBold.ttf", fontSize);
    m_io->FontDefault = m_io->Fonts->AddFontFromFileTTF("WolfEditor/data/fonts/OpenSans-Regular.ttf", fontSize);

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // ImGui Recommends this for multi windows
    ImGuiStyle& style = ImGui::GetStyle();
    if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImVec4* colors = style.Colors;
    
    // Headers
    colors[ImGuiCol_Header]        = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);  // Dark red
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.0f, 0.0f, 1.0f);  // Brighter red when hovered
    colors[ImGuiCol_HeaderActive]  = ImVec4(0.35f, 0.0f, 0.0f, 1.0f);

    // Buttons
    colors[ImGuiCol_Button]        = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);    // Buttons (idle)
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.05f, 0.05f, 1.0f);  // Buttons (hovered)
    colors[ImGuiCol_ButtonActive] =  ImVec4(0.15f, 0.05f, 0.05f, 1.0f);

    // Frame BG (Input fields, sliders, etc.)
    colors[ImGuiCol_FrameBg]        = ImVec4(0.15f, 0.05f, 0.05f, 1.0f); // idle
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.08f, 0.08f, 1.0f); // hover
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.35f, 0.12f, 0.12f, 1.0f); // active


    // Tabs
    colors[ImGuiCol_Tab]                = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);  // Dark red idle
    colors[ImGuiCol_TabHovered]         = ImVec4(0.35f, 0.05f, 0.05f, 1.0f); // Brighter red hover
    colors[ImGuiCol_TabActive]          = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);  // Active tab = bold red
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.1f, 0.0f, 0.0f, 1.0f);  // Unfocused = darker
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.0f, 0.0f, 1.0f); // Unfocused but active = slightly brighter

    // Title bar
    colors[ImGuiCol_TitleBg]            = ImVec4(0.15f, 0.0f, 0.0f, 1.0f); // Dark red background
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.3f, 0.0f, 0.0f, 1.0f);  // Stronger red when window active
    colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.1f, 0.0f, 0.0f, 1.0f);  // Dim red when collapsed

    // Borders
    colors[ImGuiCol_Border]       = ImVec4(0.4f, 0.0f, 0.0f, 0.6f);  // subtle dark red border
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // no extra shadow

    // Nav highlight (keyboard/gamepad selection)
    colors[ImGuiCol_NavHighlight] = ImVec4(0.8f, 0.0f, 0.0f, 0.4f);  // soft red glow

    // Docking tab highlight fix
    colors[ImGuiCol_DockingPreview] = ImVec4(0.8f, 0.0f, 0.0f, 0.6f);   // preview highlight when dragging
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.1f, 0.0f, 0.0f, 1.0f);   // background when empty


    // Layout
    style.WindowPadding   = ImVec2(8, 8);   // Space between window edges and content
    style.FramePadding    = ImVec2(6, 4);   // Padding inside widgets (buttons, inputs, etc.)
    style.ItemSpacing     = ImVec2(8, 6);   // Space between individual UI elements

    // Roundings
    style.WindowRounding  = 6.0f;  // Rounded corners on windows
    style.FrameRounding   = 4.0f;  // Rounded corners on buttons, input boxes
    style.GrabRounding    = 4.0f;  // Rounded handle for sliders/scrollbars

    // Initialize backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core"); // GLSL version string

    // Add editor windows

    AddWindow(new GameViewWindow(gameView));

    AddWindow(new HierarchyWindow(-1));

    AddWindow(new InspectorWindow(-1));
    
    AddWindow(new StatsWindow());

    AddWindow(new SceneViewWindow(sceneView));


    if (auto hierarchyWindow = dynamic_cast<HierarchyWindow*>(FindWindow("Hierarchy"))) {
        hierarchyWindow->SetInspectorWindow(FindWindow("Inspector"));
    }
}

void Imgui::DrawMainMenuBar(){
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 8.0f)); // x = horiz padding, y = vertical padding
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 5.0f)); // spacing between menu items
    
    if (ImGui::BeginMainMenuBar())
    {

        static bool savePopupOpen = false;
        static char filename[128] = "scene.yaml"; // default name

        static bool openSavePopup = false;
        static bool openOpenPopup = false;
        


        // Basic File Menu
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
                
            }
            if (ImGui::MenuItem("Open Scene...", "Ctrl+O")) {
                openOpenPopup = true;
            }
            if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
                openSavePopup = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) { 
                // close the app
            }
            ImGui::EndMenu();
        }

        if(openSavePopup){
            ImGui::OpenPopup("Save Scene");
            openSavePopup = false;
        }
        if(openOpenPopup){
            ImGui::OpenPopup("Open Scene");
            openOpenPopup = false;
        }

        // Modal for Save Scene
        if (ImGui::BeginPopupModal("Save Scene"))
        {
            ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));

            if (ImGui::Button("Save"))
            {
                wolf::Engine::Instance().GetSceneManager().SaveActiveScene(filename);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        // Modal for Open Scene
        if (ImGui::BeginPopupModal("Open Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Filename", filename, IM_ARRAYSIZE(filename));

            if (ImGui::Button("Open"))
            {
                wolf::Engine::Instance().GetSceneManager().LoadSceneFromFile(filename);
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        // Playing game exe in editor
        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Play", "F5")) {
                wolf::Engine::Instance().SetPlaying(true);
            }
            if (ImGui::MenuItem("Pause", "F6")) {
                // Basically just pauses the updates
                wolf::Engine::Instance().SetPlaying(false);
            }
            if (ImGui::MenuItem("Stop", "Shift+F5")) {
                // Swap back to the Scene View
                wolf::Engine::Instance().SetPlaying(false);
            }
            ImGui::EndMenu();
        }

        // Toggle windows on and off
        if(ImGui::BeginMenu("Windows")){
            // Toggles windows on and off
            if(ImGui::MenuItem("Hierachy")) {}
            if(ImGui::MenuItem("Inspector")) {}
            if(ImGui::MenuItem("Stats")) {
                // This should be better implemented for each window
                auto statsWindow = FindWindow("Stats");
                
                if(statsWindow && statsWindow->IsVisible()) {
                    statsWindow->SetVisible(false);
                } else {
                    if (statsWindow) {
                        statsWindow->SetVisible(true);
                    }
                }
            }
            if(ImGui::MenuItem("Game View")) {}
            ImGui::EndMenu();
        }
        
        // // Tools to help with development
        // if(ImGui::BeginMenu("Tools"))
        // {
        //     if (ImGui::MenuItem("Asset Importer")) {}
        //     if (ImGui::MenuItem("Profiler")) {}
        //     if (ImGui::MenuItem("Shader Editor")) {}
        //     ImGui::EndMenu();
        // }

        // if (ImGui::BeginMenu("Help"))
        // {
        //     if (ImGui::MenuItem("Documentation")) {}
        //     if (ImGui::MenuItem("About")) {}
        //     ImGui::EndMenu();
        // }

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