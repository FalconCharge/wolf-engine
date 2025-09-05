#include "render/Mesh.h"


namespace wolf{
    void Mesh::SetVertices(void* pData, size_t size){
        m_VB= BufferManager::CreateVertexBuffer(pData, size);
    }
    void Mesh::SetIndices(void* pData, size_t sizeInBytes)
    {
        unsigned int numIndices = static_cast<unsigned int>(sizeInBytes / sizeof(unsigned short));
        m_IB = BufferManager::CreateIndexBuffer(static_cast<const unsigned short*>(pData), numIndices);
    }

    void Mesh::CreateBuffers(){
        
    }

}