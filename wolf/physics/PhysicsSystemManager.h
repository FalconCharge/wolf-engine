#pragma once

// The Jolt headers don't include Jolt.h. Always include Jolt.h before including any other Jolt header.
// You can use Jolt.h in your precompiled header to speed up compilation.
#include <Jolt/Jolt.h>


#include "CollisionFilters.h"
#include "DebugCallbacks.h"
#include "Listeners.h"
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/RegisterTypes.h>

#include "components/PhysicsBodyComponent.h"

#include <iostream>



class PhysicsSystemManager{
    public:
        PhysicsSystemManager();
        ~PhysicsSystemManager();

        void Shutdown();

        void Update(float deltaTime);

        JPH::PhysicsSystem& GetSystem(){return m_System;}
        JPH::BodyInterface& GetBodyInterface(){return m_System.GetBodyInterface();}

    private:

        JPH::PhysicsSystem m_System;
        JPH::JobSystemThreadPool* m_JobSystem;
        JPH::TempAllocatorImpl* m_TempAllocator;

        // These must live as long as PhysicsSystem
        BPLayerInterfaceImpl m_BPLayerInterface;
        ObjectLayerPairFilterImpl m_ObjectPairFilter;
        ObjectVsBroadPhaseLayerFilterImpl m_ObjectVsBroadPhaseFilter;
        MyContactListener m_ContactListener;
        MyBodyActivationListener m_ActivationListener;

};
