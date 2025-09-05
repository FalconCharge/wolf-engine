#pragma once
#include "core/Component.h"
#include "render/Material.h"

namespace wolf{
    class MeshRender : public Component{
        MeshRender();
        ~MeshRender();

        void Init();
        void Update();
        void Render();
    };
}