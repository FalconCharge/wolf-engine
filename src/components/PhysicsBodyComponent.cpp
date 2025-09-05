#include "components/PhysicsBodyComponent.h"

namespace wolf{

    PhysicsBodyComponent::PhysicsBodyComponent(){

    }

    PhysicsBodyComponent::~PhysicsBodyComponent(){

    }

    void PhysicsBodyComponent::Init(){

    }

    void PhysicsBodyComponent:: Update(float dt){
        // Should update the physics of the go it's attached to here and sync the transforms
    }

    void PhysicsBodyComponent::Render(){
        // Not sure if this is needed;
    }


    void PhysicsBodyComponent::DrawInspector(){
        // Use ImGUI to draw whatever should be in the inspector
    }
}