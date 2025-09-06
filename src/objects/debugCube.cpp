#include "objects/debugCube.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// Temp include for testing componets
#include "components/TestComponent.h"
#include "components/PhysicsBodyComponent.h"

#include "core/Engine.h"

#include <iostream>

DebugCube::DebugCube()
{
    Init();
}

DebugCube::~DebugCube(){
    std::cout << "Deleting GameObject " << std::endl;
    wolf::ProgramManager::DestroyProgram(m_Program);
    wolf::BufferManager::DestroyBuffer(m_VertexBuffer);
    wolf::BufferManager::DestroyBuffer(m_IndexBuffer);
    delete m_Decl;
    wolf::MaterialManager::DestroyMaterial(m_Material);
}


void DebugCube::Init(){
    // Chat GPT generated cube data
    // Define 24 vertices (6 faces × 4 verts)
    m_Vertices = {
        // Front (Z+ : Blue)
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // 0 bottom left
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // 1 bottom right
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // 2 top right
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // 3 top left

        // Back (Z- : Dark Blue)
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)}, // 4 bottom left
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)}, // 5 bottom right
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)}, // 6 top right
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)}, // 7 top left

        // Left (X- : Dark Red)
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)}, // 8 bottom left
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)}, // 9 bottom right
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)}, // 10 top right
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)}, // 11 top left

        // Right (X+ : Bright Red)
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // 12 bottom left
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // 13 bottom right
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // 14 top right
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // 15 top left

        // Top (Y+ : Bright Green)
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // 16 bottom left
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // 17 bottom right
        DebugCubeVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // 18 top right
        DebugCubeVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // 19 top left

        // Bottom (Y- : Dark Green)
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)}, // 20 bottom left
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)}, // 21 bottom right
        DebugCubeVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)}, // 22 top right
        DebugCubeVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)}  // 23 top left
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
    m_Material->SetProgram("wolf/data/debugCube.vsh", "wolf/data/DebugCube.fsh");

    // Just makes the cube abit darker
    m_Material->SetUniform("u_color", glm::vec3(0.7f, 0.7f, 0.7f));

    m_Decl = new wolf::VertexDeclaration();
    m_Decl->Begin();
    m_Decl->SetVertexBuffer(m_VertexBuffer);
    m_Decl->SetIndexBuffer(m_IndexBuffer);
    m_Decl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_Decl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_Float);
    m_Decl->End();

    //Temp
    // Adds the Test component to make sure we are updating the components
    this->AddComponent<wolf::TestComponent>();
    this->AddComponent<wolf::PhysicsBodyComponent>(false)->Init();

}

void DebugCube::Render(glm::mat4 view, glm::mat4 proj)
{
    // Render cube
    // This would be a nice upgrade
    //wolf::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, m_Program);
    
    glm::mat4 world = GetTransform().GetWorldMatrix();
    m_Material->SetUniform("world", world);

    m_Material->SetUniform("projection", proj);
    m_Material->SetUniform("view", view);

    m_Material->Apply();
    m_Decl->Bind();


    glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_SHORT, 0);


}
