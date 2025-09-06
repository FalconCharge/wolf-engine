#include "components/PhysicsBodyComponent.h"

#include "core/Engine.h"
namespace wolf{

    PhysicsBodyComponent::PhysicsBodyComponent(bool isDymanic) : m_IsDynamic(isDymanic){
        
    }

    PhysicsBodyComponent::~PhysicsBodyComponent(){
        // Remove the body if it exist
        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();
        if(!m_BodyID.IsInvalid()){
            bodyInterface.RemoveBody(m_BodyID);
            bodyInterface.DestroyBody(m_BodyID);
        }
    }

    void PhysicsBodyComponent::Init(){


        // auto comp = GetGameObjectOwner()->GetComponent<PhysicsBodyComponent>();
        // if (comp) {
        //     // Convert shared_ptr to weak_ptr
        //     std::weak_ptr<PhysicsBodyComponent> weakComp = comp;
        //     SceneManager::Instance().GetActiveScene()->GetPhysicsManager()->AddPhysicsComponent(weakComp);
        // }

        

        auto go = GetGameObjectOwner();
        auto& transform = go->GetTransform();

        // Convert to Jolt's vec
        RVec3 position(transform.GetWorldPosition().x, transform.GetWorldPosition().y, transform.GetWorldPosition().z);
        Quat rotation = Quat::sIdentity();

        RefConst<Shape> shape = new BoxShape(JPH::Vec3(transform.GetWorldScale().x, transform.GetWorldScale().y, transform.GetWorldScale().z));

        BodyCreationSettings settings(
            shape, position, rotation, 
            m_IsDynamic ? JPH::EMotionType::Dynamic : EMotionType::Static,
            m_IsDynamic ? Layers::MOVING : Layers::NON_MOVING
        );

        // Allows swithcing between static and dynamic mainly on for the editor
        settings.mAllowDynamicOrKinematic = true;

        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();
        m_BodyID = bodyInterface.CreateAndAddBody(settings, EActivation::Activate);
    }   

    void PhysicsBodyComponent:: Update(float dt){
        // Should update the physics of the go it's attached to here and sync the transforms
        if(m_BodyID.IsInvalid()) return;

        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();

        RVec3 pos = bodyInterface.GetPosition(m_BodyID);
        Quat rot = bodyInterface.GetRotation(m_BodyID);

        // Sync Physics to GO
        // auto go = GetGameObjectOwner();
        //go->GetTransform().SetPosition({ pos.GetX(), pos.GetY(), pos.GetZ() });

        SyncTransformFromPhysics();

    }

    void PhysicsBodyComponent::Render(){
        // Not sure if this is needed;
    }

    void PhysicsBodyComponent::_ResetBody(){
        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();

        // If a body already exists, remove it first
        if (m_BodyID.IsInvalid() == false) {
            bodyInterface.RemoveBody(m_BodyID);
            bodyInterface.DestroyBody(m_BodyID);
            m_BodyID = JPH::BodyID(); // Reset to invalid
        }

        // Now create a fresh one
        Init();
    }

    void PhysicsBodyComponent::SyncTransformFromPhysics()
    {
        if (m_BodyID.IsInvalid()) return;

        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();


        RVec3 pos = bodyInterface.GetPosition(m_BodyID);
        Quat rot = bodyInterface.GetRotation(m_BodyID);

        auto go = GetGameObjectOwner();
        go->GetTransform().SetPosition({ pos.GetX(), pos.GetY(), pos.GetZ() });
        go->GetTransform().SetRotation({ rot.GetX(), rot.GetY(), rot.GetZ(), rot.GetW() });
    }



    void PhysicsBodyComponent::DrawInspector(){
        // Use ImGUI to draw whatever should be in the inspector
        if (ImGui::CollapsingHeader("Physics Body")) {


        auto& bodyInterface = Engine::Instance().GetPhysicsSystem().GetBodyInterface();

            // Static / Dynamic toggle
            bool dyn = m_IsDynamic;
            if (ImGui::Checkbox("Dynamic", &dyn)) {
                m_IsDynamic = dyn;
                bodyInterface.SetMotionType(m_BodyID, m_IsDynamic ? EMotionType::Dynamic : EMotionType::Static, EActivation::Activate);
            }

            if (ImGui::SliderFloat("Friction", &m_Friction, 0.0f, 2.0f)) {
                bodyInterface.SetFriction(m_BodyID, m_Friction);
            }

            if (ImGui::SliderFloat("Restitution", &m_Restitution, 0.0f, 1.0f)) {
                bodyInterface.SetRestitution(m_BodyID, m_Restitution);
            }

            float velocity[3] = { m_LinearVelocity.GetX(), m_LinearVelocity.GetY(), m_LinearVelocity.GetZ() };
            if (ImGui::InputFloat3("Velocity", velocity)) {
                m_LinearVelocity = JPH::Vec3(velocity[0], velocity[1], velocity[2]);
                bodyInterface.SetLinearVelocity(m_BodyID, m_LinearVelocity);
            }

            // --- Position ---
            JPH::RVec3 position = bodyInterface.GetPosition(m_BodyID); // Get current position
            float pos[3] = { (float)position.GetX(), (float)position.GetY(), (float)position.GetZ() };
            if (ImGui::InputFloat3("Position", pos)) {
                bodyInterface.SetPosition(m_BodyID, JPH::RVec3(pos[0], pos[1], pos[2]), JPH::EActivation::DontActivate);
            }

            if (ImGui::Button("Reset the physics Body")) {
                _ResetBody();
            }


        }

    }
}