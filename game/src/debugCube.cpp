#include "debugCube.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

DebugCube::DebugCube()
{
    // Define 24 vertices (6 faces × 4 verts)
    m_Vertices = {
        // Front (Z+)
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},   // 0 bottom left
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},   // 1 bottom right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},   // 2 top right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},   // 3 top left

        // Back (Z-)
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},   // 4 bottom left
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},   // 5 bottom right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},   // 6 top right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},   // 7 top left

        // Left (X-)
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 8 bottom left
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 9 bottom right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 10 top right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 11 top left

        // Right (X+)
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 12 bottom left
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 13 bottom right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 14 top right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},   // 15 top left

        // Top (Y+)
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},   // 16 bottom left
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},   // 17 bottom right
        DebugCubeVertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},   // 18 top right
        DebugCubeVertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},   // 19 top left

        // Bottom (Y-)
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)},   // 20 bottom left
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)},   // 21 bottom right
        DebugCubeVertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)},   // 22 top right
        DebugCubeVertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}    // 23 top left
    };

    // Indices (two triangles per face)
    m_Indices = {
        // Front
        0, 1, 2,  0, 2, 3,
        // Back
        4, 5, 6,  4, 6, 7,
        // Left
        8, 9, 10, 8, 10, 11,
        // Right
        12, 13, 14, 12, 14, 15,
        // Top
        16, 17, 18, 16, 18, 19,
        // Bottom
        20, 21, 22, 20, 22, 23
    };


    m_VertexBuffer = wolf::BufferManager::CreateVertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(DebugCubeVertex));
    m_IndexBuffer = wolf::BufferManager::CreateIndexBuffer(m_Indices.data(), static_cast<unsigned int>(m_Indices.size()));


    m_Material = wolf::MaterialManager::CreateMaterial("Basic");
    m_Material->SetProgram("game/data/debugCube.vsh", "game/data/debugCube.fsh");

    // Just makes the cube abit darker
    m_Material->SetUniform("u_color", glm::vec3(0.7f, 0.7f, 0.7f));

    m_Decl = new wolf::VertexDeclaration();
    m_Decl->Begin();
    m_Decl->SetVertexBuffer(m_VertexBuffer);
    m_Decl->SetIndexBuffer(m_IndexBuffer);
    m_Decl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_Decl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_Float);
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

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 10.0f);  // Move 10 units back
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