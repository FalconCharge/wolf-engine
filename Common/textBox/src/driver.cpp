#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../../wolf/wolf.h"

#include "Quad.h"
#include "ProcessFile.h"
#include "TextTable.h"
#include "TextBox.h"

/*
// This should be developed into a method which can be ran in the main
*/
class Driver : public wolf::App {
public:
    

    Driver(const std::string& name) : wolf::App(name){
        Sample1();
    }

    void Sample1()
    {
        SetUpTextTable();
        TextBoxLeftAlign();
        TextBoxRightAlign();
        TextBoxCenterAlign();
    }

    void update(float dt) override {
        // Update application logic here
    }

    void render() override {
        // Render graphics here
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);  //Sets the screen to a dark blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Renders 3 different textBoxes
        pTextBox->render(m_width, m_height); // Render the generated quads
        pTextBox2->render(m_width, m_height);
        pTextBox3->render(m_width, m_height);
    }
    
    void TextBoxRightAlign(){
        pTextBox3 = new TextBox("Data/FontData/script.fnt", table->GetString("str_course_name") + " OverFlow", 300.0f, 125.0f);
        pTextBox3->SetBackroundColor(glm::vec4(0.5, 1, 0.5, 0.5));
        pTextBox3->setColor(glm::vec4(1, 0.5, 0.5, 1));
        pTextBox3->SetPosition(glm::vec2(200, 400)); // Set initial position
        pTextBox3->SetHorizontalAlignment("AL_Right");
        pTextBox3->Init();
    }
    void TextBoxCenterAlign(){
        pTextBox = new TextBox("Data/FontData/font.fnt", table->GetString("str_course_name"), 400.0f, 250.0f);
        pTextBox->SetBackroundColor(glm::vec4(1, 0.5, 0, 0.5));
        pTextBox->setColor(glm::vec4(1, 1, 1, 1));
        pTextBox->SetPosition(glm::vec2(100, 700)); // Set initial position
        pTextBox->SetHorizontalAlignment("AL_Center");
        pTextBox->Init();
    }
    void TextBoxLeftAlign(){
        pTextBox2 = new TextBox("Data/FontData/TNR100.fnt", table->GetString("str_course_name"), 400.0f, 300.0f);
        
        pTextBox2->setColor(glm::vec4(1, 0, 1, 1));
        pTextBox2->SetPosition(glm::vec2(555.0f)); // Set initial position
        pTextBox2->SetHorizontalAlignment("AL_Left");
        pTextBox2->Init();

    }
    void SetUpTextTable(){
        // Create a TextTable object and load the file
        table = new TextTable("Data/sample.tsv");
        // Set the language to English
        table->SetLanguage("English");
    }
    
private:
    TextBox* pTextBox;
    TextBox* pTextBox2;
    TextBox* pTextBox3;

    TextTable* table;
};
/*
int main(){
    Driver app("TextRendering");
    app.run();
    return 0;    
}*/


