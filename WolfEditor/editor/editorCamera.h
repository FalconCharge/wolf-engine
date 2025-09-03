#pragma once
#include "core/Camera.h"
#include "core/InputManager.h"
#include <glm/glm.hpp>

class EditorCamera : public wolf::Camera {
public:
    EditorCamera(float fov, float aspect, float nearClip, float farClip);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    float m_Yaw;
    float m_Pitch;
    float m_Speed;
    float m_Sensitivity;
    float m_Aspect;
};
