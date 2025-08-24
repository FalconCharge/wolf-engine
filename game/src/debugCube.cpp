#include "debugCube.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

DebugCube::DebugCube()
{
    // Initialize cube properties
    // Define 4 corners of a square (XY plane, Z=0)
    m_Vertices = {
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 0.0f)},   // Bottom left
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 0.0f)},   // Bottom right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 0.0f)},   // Top right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 0.0f)},   // Top left
    };

    // Two triangles (0-1-2, 2-3-0)
    m_Indices = {
        // Bottom Right side triangle
        0, 1, 2,

        // Top left side triangle
        0, 2, 3
    };

    m_VertexBuffer = wolf::BufferManager::CreateVertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(DebugCubeVertex));
    m_IndexBuffer = wolf::BufferManager::CreateIndexBuffer(m_Indices.data(), static_cast<unsigned int>(m_Indices.size()));

    // Load a basic shader program (you’d need to have these shader files)
    m_Program = wolf::ProgramManager::CreateProgram("game/data/basic.vsh", "game/data/basic.fsh");

    m_Material = wolf::MaterialManager::CreateMaterial("Basic");
    m_Material->SetProgram("game/data/basic.vsh", "game/data/basic.fsh");

    m_Material->SetUniform("u_color", glm::vec3(1.0f, 0.0f, 0.0f));

    m_Decl = new wolf::VertexDeclaration();
    m_Decl->Begin();
    m_Decl->SetVertexBuffer(m_VertexBuffer);
    m_Decl->SetIndexBuffer(m_IndexBuffer);
    m_Decl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_Decl->End();
    

}

DebugCube::~DebugCube(){
    wolf::ProgramManager::DestroyProgram(m_Program);
}

void DebugCube::Update(float dt)
{

}

void DebugCube::Render()
{
    // Render cube
    // This would be a nice upgrade
    //wolf::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, m_Program);
    
    glm::mat4 world = GetTransform().GetWorldMatrix();
    m_Material->SetUniform("world", world);

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, -10.0f);  // Move 10 units back
    glm::vec3 cameraTarget= glm::vec3(0.0f, 0.0f, 0.0f);  // Look at origin
    glm::vec3 up          = glm::vec3(0.0f, 1.0f, 0.0f);  // World up

    glm::mat4 view = glm::lookAt(
        cameraPos,    // Camera position
        cameraTarget, // Point to look at
        up            // World up vector
    );

    float fov = glm::radians(45.0f);       // Field of view (in radians!)
    float aspect = (float)1920 / (float)1080;  // From framebuffer size
    float nearPlane = 0.1f;
    float farPlane  = 100.0f;

    glm::mat4 proj = glm::perspective(fov, aspect, nearPlane, farPlane);


    m_Material->SetUniform("projection", proj);
    m_Material->SetUniform("view", view);

    m_Material->Apply();
    m_Decl->Bind();


    glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_SHORT, 0);


}