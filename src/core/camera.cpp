#include "core/camera.h"
namespace wolf{



void Camera::Init(){
    CreateFrustumFromCamera();
}
void Camera::update(float dt) {
    //Create a new frustum based on new location
    
    if(!m_bPauseFrustum){
        CreateFrustumFromCamera();
        //std::cout << "creating frustum" << std::endl;
    }

    glm::vec2 delta = wolf::InputManager::Instance().GetMouseDelta();

    float offsetX = delta.x;
    float offsetY = m_inverted ? -delta.y : delta.y;

    // Sensitivity settings for camera movement
    const float sensitivity = 0.05f;
    offsetX *= sensitivity; 
    offsetY *= sensitivity;

    // Update yaw and pitch based on mouse movement
    m_yaw += offsetX;
    m_pitch += offsetY;

    //Limits from player looking to high
    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

    // Update the front vector based on yaw and pitch
    UpdateCameraVectors();

    glm::vec3 forwardXZ = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
    glm::vec3 rightXZ = glm::normalize(glm::cross(forwardXZ, glm::vec3(0.0f, 1.0f, 0.0f)));

    float cameraSpeed = 2.0f * dt; // Adjust speed based on frame time (dt)
    DetectInput(cameraSpeed, forwardXZ, rightXZ);
}

// void Camera::DetectInput(float &cameraSpeed, glm::vec3 &forwardXZ, glm::vec3 &rightXZ)
// {
//     // TODO: Change this to the new input system
//     if (m_pApp->isKeyDown(GLFW_KEY_LEFT_SHIFT))
//     {
//         cameraSpeed *= 4;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_W))
//     {
//         m_position += forwardXZ * cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_S))
//     {
//         m_position -= forwardXZ * cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_A))
//     {
//         m_position -= rightXZ * cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_D))
//     {
//         m_position += rightXZ * cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_Q))
//     {
//         m_position.y -= cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_E))
//     {
//         m_position.y += cameraSpeed;
//     }
//     if (m_pApp->isKeyDown(GLFW_KEY_I))
//     { // Press 'I' to toggle inversion
//         this->InvertCamera();
//     }
// }
void Camera::DetectInput(float &cameraSpeed, glm::vec3 &forwardXZ, glm::vec3 &rightXZ)
{
    auto& input = wolf::InputManager::Instance();
    if (input.IsKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        cameraSpeed *= 4.0f;
    }
    if (input.IsKeyDown(GLFW_KEY_W))
    {
        m_position += forwardXZ * cameraSpeed;
    }
    if (input.IsKeyDown(GLFW_KEY_S))
    {
        m_position -= forwardXZ * cameraSpeed;
    }
    if (input.IsKeyDown(GLFW_KEY_A))
    {
        m_position -= rightXZ * cameraSpeed;
    }
    if (input.IsKeyDown(GLFW_KEY_D))
    {
        m_position += rightXZ * cameraSpeed;
    }
    if (input.IsKeyDown(GLFW_KEY_Q))
    {
        m_position.y -= cameraSpeed;
    }
    if (input.IsKeyDown(GLFW_KEY_E))
    {
        m_position.y += cameraSpeed;
    }  
    // Should change this to pressed
    if (input.IsKeyDown(GLFW_KEY_I))
    {
        this->InvertCamera();
    }
}


void Camera::UpdateCameraVectors() {
    // Calculate the new front vector based on yaw and pitch
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Also re-calculate the right and up vectors
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Cross product with up vector
    m_up = glm::normalize(glm::cross(m_right, m_front));  // Up vector
}
glm::mat4 Camera::GetViewMatrix(){      
    return glm::lookAt(m_position, m_position + m_front, m_up);
}
glm::mat4 Camera::GetProjMatrix() {
    return glm::perspective(m_fov, m_Aspect, m_near, m_far);
}
glm::vec3 Camera::GetViewPosition(){
    return m_position;
}
void Camera::InvertCamera(){
    m_inverted = !m_inverted;
}
void Camera::SetScreenSize(glm::vec2 screenSize) {
    m_screenWidth = screenSize.x;
    m_screenHeight = screenSize.y;
}

void Camera::CreateFrustumFromCamera()
{
    const float halfVSide = m_far * tanf(m_fov * 0.5f);
    const float halfHSide = halfVSide * m_Aspect;
    const glm::vec3 frontMultFar = glm::vec3(m_far * m_front);

    m_frustum.nearFace = { GetViewPosition() + m_near * m_front, m_front };
	m_frustum.farFace = { GetViewPosition() + frontMultFar, -m_front };
	m_frustum.rightFace = { GetViewPosition(), glm::cross(frontMultFar - m_right * halfHSide, m_up) };
	m_frustum.leftFace = { GetViewPosition(), glm::cross(m_up, frontMultFar + m_right * halfHSide) };
	m_frustum.topFace = { GetViewPosition(), glm::cross(m_right, frontMultFar - m_up * halfVSide) };
	m_frustum.bottomFace = {GetViewPosition(), glm::cross(frontMultFar + m_up * halfVSide, m_right)};

}
void Camera::PauseFrustum(){
    m_bPauseFrustum = !m_bPauseFrustum;
}
}