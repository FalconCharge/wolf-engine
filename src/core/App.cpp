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

void _mouseScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset)
{
    App* pApp = (App*) glfwGetWindowUserPointer(pWindow);
    pApp->_setMouseScroll(glm::vec2((float)xoffset,(float)yoffset));
}

App::App(const std::string& name)
  : m_name(name)
{
    _init();
    for(int i = 0; i < NUM_KEYS; ++i)
    {
        m_lastKeysDown[i] = false;
    }
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
    glfwSetScrollCallback(m_pWindow, _mouseScrollCallback);
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

    for(int i = 0; i < NUM_KEYS; ++i)
    {
        m_lastKeysDown[i] = isKeyDown(GLFW_KEY_SPACE + i);
    }
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

        m_mouseScroll = glm::vec2(0.0f,0.0f);
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        InputManager::Instance().Update();
    }

}

bool App::isKeyDown(int key) const
{
    key = toupper(key);
    return glfwGetKey(m_pWindow,key) == GLFW_PRESS;
}

bool App::isKeyJustDown(int key) const
{
    key = toupper(key);
    return glfwGetKey(m_pWindow,key) == GLFW_PRESS && !m_lastKeysDown[key-GLFW_KEY_SPACE];
}

bool App::isLMBDown() const
{
    int state = glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT);
    return state == GLFW_PRESS;
}

bool App::isRMBDown() const
{
    int state = glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT);
    return state == GLFW_PRESS;
}

bool App::isMMBDown() const
{
    int state = glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_MIDDLE);
    return state == GLFW_PRESS;
}

glm::vec2 App::getMousePos() const
{
    double xpos, ypos;
    glfwGetCursorPos(m_pWindow, &xpos, &ypos);
    return glm::vec2((float)xpos,(float)ypos);
}

glm::vec2 App::getScreenSize() const
{
    int w,h;
    glfwGetFramebufferSize(m_pWindow, &w, &h);
    return glm::vec2((float)w,(float)h);
}

void App::_setMouseScroll(const glm::vec2& scroll)
{
    m_mouseScroll = scroll;
}

}