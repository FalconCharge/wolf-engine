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
