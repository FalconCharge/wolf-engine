#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>

#include "core/Component.h"

namespace wolf {
    class PhysicsBodyComponent : public Component{
        public:

            PhysicsBodyComponent();
            ~PhysicsBodyComponent();

            void Init() override;

            void Update(float dt) override;

            void Render() override;

            void DrawInspector();

        private:
            JPH::BodyID bodyID;
            bool dynamic;
    };
}
