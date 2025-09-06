// ------------------------------------------------------------
// Class: Mesh
// Brief: My Lazy attemp to make a Mesh; Was planned to use in the component class
//      wolf has a Model class that might do this for us though. But I can't get it to work
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
#pragma once
#include "BufferManager.h"
namespace wolf
{
    class Mesh{
        public:
            Mesh() = default;
            ~Mesh();

            void SetVertices(void* vertexData, size_t);
            void SetIndices(void* indexData, size_t);

            
            void CreateBuffers();
            void Bind();
            void Draw();



        private:

            void* m_vertexData;
            void* m_indexData;
            size_t m_vertexSize = 0;
            size_t m_indexSize = 0;

            VertexBuffer* m_VB = nullptr;
            IndexBuffer* m_IB = nullptr;

    };
} // namespace wolf
