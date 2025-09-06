#include "core/App.h"
#include "render/RenderTarget.h"
#include <stdlib.h>
#include <stdio.h>
#if _WIN32
#include <windows.h>
#endif

// Icon

#include "core/InputManager.h"
#include "stb_image.h"
#include "core/Engine.h"

namespace wolf
{

void _fatalError(const char* msg) 
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void _errorCallback(int error, const char* description)
{
    _fatalError(description);
}

App::App(const std::string& name)
  : m_name(name)
{
    _init();
    wolf::InputManager::Instance().Initialize(m_pWindow);
}

App::~App()
{

}

void App::_init()
{

#if _WIN32

    char dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, dir);

    // If we are inside build/bin/Debug or build/bin/Release, go up 3
    if (strstr(dir, "\\build\\bin\\DEBUG") || strstr(dir, "\\build\\bin\\Release")) {
        SetCurrentDirectory("..\\..\\..");
    }

    char verify[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, verify);
    printf("Working directory: %s\n", verify);
#endif

    if (!glfwInit())
        _fatalError("Failed to init GLFW\n");

    printf("Successfully initialized GLFW\n");
    glfwSetErrorCallback(_errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if 0
    int numMonitors = 0;
    GLFWmonitor** ppMonitors = glfwGetMonitors(&numMonitors);
    GLFWmonitor* pMonitorToUse = ppMonitors[0];
    int resX = 1280;
    int resY = 720;

    for(int i = 0; i < numMonitors; i++)
    {
        const char* name = glfwGetMonitorName(ppMonitors[i]);
        int x,y,w,h;

        glfwGetMonitorWorkarea(ppMonitors[i], &x, &y, &w, &h);

        if(w == 2560)
        {
            pMonitorToUse = ppMonitors[i];
            resX = w;
            resY = h;
        }
    }
#else
    int resX = 1280;
    int resY = 720;
    // int resX = 1920;
    // int resY = 1080;
    GLFWmonitor* pMonitorToUse = nullptr; // Windowed

    // Full Screen option
    //GLFWmonitor* pMonitorToUse = glfwGetPrimaryMonitor(); // fullscreen
    //const GLFWvidmode* mode = glfwGetVideoMode(pMonitorToUse);
#endif

    m_pWindow = glfwCreateWindow(resX, resY, m_name.c_str(), pMonitorToUse, NULL);
    if (!m_pWindow)
        _fatalError("Couldn't create window\n");

    glfwSetWindowUserPointer(m_pWindow, this);
    glfwMakeContextCurrent(m_pWindow);

    // Enable vsync
    //glfwSwapInterval(1);
    // Disable vsync
    glfwSwapInterval(0);

    GLenum err = glewInit();
    if (GLEW_OK != err)
        _fatalError((const char*)glewGetErrorString(err));
    else   
        printf("Successfully initialized GLEW\n");

    RenderTarget::InitScreen(resX, resY);



    // TODO: Setup Game Icon VS Engine Icon
    // Setting up Icon
    GLFWimage images[2];
    images[0].pixels = stbi_load("wolf/data/falconlogo64.png", &images[0].width, &images[0].height, 0, 4);
    images[1].pixels = stbi_load("wolf/data/falconlogo128.png", &images[1].width, &images[1].height, 0, 4);

    if (images[0].pixels && images[1].pixels) {
        glfwSetWindowIcon(m_pWindow, 2, images);  // 2 icons, GLFW picks best fit
    }

    // Free memory after GLFW copies the pixels
    if (images[0].pixels) stbi_image_free(images[0].pixels);
    if (images[1].pixels) stbi_image_free(images[1].pixels);



    // Don't draw Back faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void App::_internalUpdate(float dt)
{
    Update(dt);
}

void App::Run()
{
    double frameCount = 0;
    double fpsTime = 0;
    float fps = 0;

    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(m_pWindow))
    {
        double currTime = glfwGetTime();
        float elapsedTime = (float)(currTime - lastTime);
        lastTime = currTime;

        fpsTime += elapsedTime;
        frameCount++;

        if(fpsTime >= 1.0)
        {
            fps = (float)frameCount;
            frameCount = 0;
            fpsTime = 0;
            EngineStats::Get().FPS = fps;
        }

         // Get framebuffer size (may be different than window size on HiDPI displays)

        glfwGetFramebufferSize(m_pWindow, &m_width, &m_height);
        if(m_width != 0 && m_height != 0)
        {
            RenderTarget::SetScreenSize(m_width,m_height);
            RenderTarget::GetScreen().Bind();

            _internalUpdate(elapsedTime);
            Render();
        }

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        InputManager::Instance().Update();
        EngineStats::Get().drawCalls = 0;   // Reset the amount of draw calls

    }

    // Shut Everything down here
    Engine::Instance().Shutdown();

}

}