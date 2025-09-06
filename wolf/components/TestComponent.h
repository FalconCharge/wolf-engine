#pragma once
#include "core/Component.h"

#include <iostream>

namespace wolf{
    class TestComponent : public Component{
        public: 
            TestComponent(){
                m_num = 0;
                m_inc = 1;
                m_TimeBTWPrint = 1;
                // std::cout << "Init testComponent" << std::endl;
            }

            ~TestComponent(){}

            void Update(float dt) override {
                m_num += m_inc * dt;

                if (m_num > m_TimeBTWPrint) {
                    std::cout << "Testing the Update function on a game Object\n";
                     //Can Grab the GO and adjust it's values from component
                    //GetGameObjectOwner()->GetTransform().DebugString();
                    m_num -= m_TimeBTWPrint;
                }
                //From this I'm hoping the Physcis component is going to work
            }


            void Render(){
                // Not testing this currently (Don't think It's nessacry in most components)
            }

            void DrawInspector() override{
                ImGui::Text("Test Component");

                // Just changed the Time BTW print kinda useful for an example of how it works
                ImGui::DragFloat("Time Between Print", &m_TimeBTWPrint, 0.1f);
            }

        private:
            float m_num;
            float m_inc;
            float m_TimeBTWPrint;
    };
}