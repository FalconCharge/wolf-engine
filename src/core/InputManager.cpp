#include "core/InputManager.h"

namespace wolf
{
    InputManager& InputManager::Instance()
    {
        static InputManager instance;
        return instance;
    }

    void InputManager::Initialize(GLFWwindow* window)
    {
        m_window = window;

        // Reset arrays
        m_keys.fill(false);
        m_lastKeys.fill(false);
        m_mouseButtons.fill(false);

        // Setup scroll callback
        glfwSetScrollCallback(window, [](GLFWwindow* win, double xoffset, double yoffset) {
            InputManager::Instance().m_scrollDelta += glm::vec2(xoffset, yoffset);
        });
    }

    void InputManager::Update()
    {
        if (!m_window)
            return;

        //DebugPrintKeysDown();
    
        m_scrollDelta = glm::vec2(0.0f);

        // Update key states
        m_lastKeys = m_keys;


        // Update curr key states
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
        {
            m_keys[key] = (glfwGetKey(m_window, key) == GLFW_PRESS);
        }

        // Mouse Buttons
        for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
        {
            m_mouseButtons[button] = (glfwGetMouseButton(m_window, button) == GLFW_PRESS);
        }

        // Mouse Position
        m_lastMousePos = m_mousePos;
        double x, y;
        glfwGetCursorPos(m_window, &x, &y);
        m_mousePos = glm::vec2(x, y);
        m_mouseDelta = m_mousePos - m_lastMousePos;


    }
    void InputManager::SetCursorLocked(bool locked)
    {
        if (!m_window) return;
        m_cursorLocked = locked;
        glfwSetInputMode(m_window, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    void InputManager::DebugPrintKeysDown() const
    {
        if (!m_inputEnabled) {
            std::cout << "Input Disabled" << std::endl;
            return;
        }

        // ----- Keyboard -----
        std::cout << "Keys currently down: ";
        bool anyKey = false;

        for (int key = 0; key <= GLFW_KEY_LAST; ++key)
        {
            if (m_keys[key])
            {
                anyKey = true;

                const char* name = glfwGetKeyName(key, 0);
                if (name)
                {
                    std::cout << "[" << name << "] ";
                }
                else
                {
                    std::cout << "[KeyCode " << key << "] ";
                }
            }
        }

        if (!anyKey)
            std::cout << "None";

        std::cout << std::endl;

        // ----- Mouse Buttons -----
        std::cout << "Mouse buttons down: ";
        bool anyMouse = false;

        for (int btn = 0; btn <= GLFW_MOUSE_BUTTON_LAST; ++btn)
        {
            if (m_mouseButtons[btn])
            {
                anyMouse = true;
                std::cout << "[Button " << btn << "] ";
            }
        }

        if (!anyMouse)
            std::cout << "None";

        std::cout << std::endl;

        // ----- Mouse Position -----
        std::cout << "Mouse position: (" << m_mousePos.x << ", " << m_mousePos.y << ")" << std::endl;
        std::cout << "Mouse delta: (" << m_mouseDelta.x << ", " << m_mouseDelta.y << ")" << std::endl;
        std::cout << "Mouse scroll: (" << m_scrollDelta.x << ", " << m_scrollDelta.y << ")" << std::endl;
    }


}
