#include "debugCube.h"

DebugCube::DebugCube()
{
    // Initialize cube properties
    // Define 4 corners of a square (XY plane, Z=0)
    m_Vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // bottom-left (red)
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // bottom-right (green)
        {{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // top-right (blue)
        {{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // top-left (yellow)
    };

    // Two triangles (0-1-2, 2-3-0)
    m_Indices = {
        0, 1, 2,
        2, 3, 0
    };

    m_VertexBuffer = wolf::BufferManager::CreateVertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(DebugCubeVertex));
    m_IndexBuffer = wolf::BufferManager::CreateIndexBuffer(m_Indices.data(), static_cast<unsigned int>(m_Indices.size()));

    // Load a basic shader program (you’d need to have these shader files)
    m_Program = wolf::ProgramManager::CreateProgram("game/data/basic.vsh", "game/data/basic.fsh");

}

DebugCube::~DebugCube(){
    wolf::ProgramManager::DestroyProgram(m_Program);
}

void DebugCube::Update(float dt)
{
    // Update cube logic
    // Not changing anythin atm
}

void DebugCube::Render()
{
    // Render cube
    // This would be a nice upgrade
    //wolf::Renderer::Submit(m_VertexBuffer, m_IndexBuffer, m_Program);

    m_Program->Bind();

    glm::mat4 world = GetTransform().GetWorldMatrix();
    m_Program->SetUniform("world", world);

    // Identity projection + view (no camera)
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    m_Program->SetUniform("projection", projection);
    m_Program->SetUniform("view", view);

    // Bind vertex + index buffers
    m_VertexBuffer->Bind();
    m_IndexBuffer->Bind();

    glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_SHORT, 0);

}