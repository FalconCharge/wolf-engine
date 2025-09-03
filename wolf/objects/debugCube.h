#pragma once
#include "core/GameObject.h"
#include "render/render.h"
#include "core/camera.h"

#include "glm/glm.hpp"

struct DebugCubeVertex
{
    glm::vec3 Position;
    glm::vec4 color;
};

class DebugCube : public wolf::GameObject
{
public:
    // Constructor Where the cube gets created
    DebugCube();

    // Deconstructor
    ~DebugCube();

    std::string GetType() const override {return "DebugCube";};

    void Init();

    // Called each frame to update the cubes properties
    void Update(float dt) override;

    // Called each frame to Draw the cube
    void Render() override;

private:

    std::vector<DebugCubeVertex> m_Vertices;
    std::vector<unsigned short> m_Indices;

    // Holds all the verts of the Cube
    wolf::VertexBuffer* m_VertexBuffer = nullptr;
    // Reduces the amount of data to go to shader
    wolf::IndexBuffer* m_IndexBuffer = nullptr;
    // Material properties for the cube
    wolf::Material* m_Material = nullptr; // Prob won't use currently
    // Shader for adding color to the cube
    wolf::Program* m_Program = nullptr;
    // For adding indexing and vertexes to bind 
    wolf::VertexDeclaration* m_Decl = nullptr;

};
