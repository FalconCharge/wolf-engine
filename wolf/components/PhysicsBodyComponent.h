#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include "core/Component.h"



#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>


namespace wolf {
    class PhysicsBodyComponent : public Component{
        public:

            PhysicsBodyComponent(bool isDymanic);
            ~PhysicsBodyComponent();

            void Init() override;

            void Update(float dt) override;

            void Render() override;

            void DrawInspector();

            void _ResetBody();

            void SyncTransformFromPhysics();

        private:
            JPH::BodyID m_BodyID = JPH::BodyID();
            bool m_IsDynamic;

            float m_Friction = 0.5f;
            float m_Restitution = 0.0f;
            JPH::Vec3 m_LinearVelocity = JPH::Vec3::sZero();
    };
}
