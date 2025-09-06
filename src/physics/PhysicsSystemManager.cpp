#include "physics/PhysicsSystemManager.h"


using namespace JPH;
using namespace JPH::literals;



    PhysicsSystemManager::PhysicsSystemManager()
        
    {
        // Register allocation hook. In this example we'll just let Jolt use malloc / free but you can override these if you want (see Memory.h).
        // This needs to be done before any other Jolt function is called.
        JPH::RegisterDefaultAllocator();

        // Install trace and assert callbacks
        JPH::Trace = TraceImpl;
        JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

        // Create a factory, this class is responsible for creating instances of classes based on their name or hash and is mainly used for deserialization of saved data.
        // It is not directly used in this example but still required.
        JPH::Factory::sInstance = new JPH::Factory();

        // Register all physics types with the factory and install their collision handlers with the CollisionDispatch class.
        // If you have your own custom shape types you probably need to register their handlers with the CollisionDispatch before calling this function.
        // If you implement your own default material (PhysicsMaterial::sDefault) make sure to initialize it before this function or else this function will create one for you.
        JPH::RegisterTypes();

        m_TempAllocator = new TempAllocatorImpl(10 * 1024 * 1024);
        m_JobSystem = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);


        // This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
        // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
        const uint32_t cMaxBodies = 1024;

        // This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
        const uint32_t cNumBodyMutexes = 0;

        // This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
        // body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
        // too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
        // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
        const uint32_t cMaxBodyPairs = 1024;

        // This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are detected than this
        // number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
        // Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
        const uint32_t cMaxContactConstraints = 1024;

        m_System.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, m_BPLayerInterface, m_ObjectVsBroadPhaseFilter, m_ObjectPairFilter);
        // Now we can create the actual physics system.

        // A body activation listener gets notified when bodies activate and go to sleep
        // Note that this is called from a job so whatever you do here needs to be thread safe.
        // Registering one is entirely optional.

        // A contact listener gets notified when bodies (are about to) collide, and when they separate again.
        // Note that this is called from a job so whatever you do here needs to be thread safe.
        // Registering one is entirely optional.

        m_System.SetBodyActivationListener(&m_ActivationListener);
        m_System.SetContactListener(&m_ContactListener);
  
    }

    PhysicsSystemManager::~PhysicsSystemManager() {
        JPH::UnregisterTypes();
        delete JPH::Factory::sInstance;
        JPH::Factory::sInstance = nullptr;

        delete m_TempAllocator;
        delete m_JobSystem;
    }

    void PhysicsSystemManager::Update(float null) {
        const float deltaTime = 1.0f/60.0f;

        const int cCollisionSteps = 1;
        m_System.Update(deltaTime, cCollisionSteps, m_TempAllocator, m_JobSystem);

        for (auto it = m_PhysicsComps.begin(); it != m_PhysicsComps.end(); ) {
        if (auto comp = it->lock()) {
            comp->SyncTransformFromPhysics();
            ++it;
        } else {
            // Component destroyed, remove weak_ptr
            it = m_PhysicsComps.erase(it);
        }
    }

    }


