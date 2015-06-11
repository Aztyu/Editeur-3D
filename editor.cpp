/* 
 * File:   editor.cpp
 * Author: Aztyu
 * 
 * Created on 26 décembre 2014, 11:29
 */

#include "Editor.h"
#include "Pointers.h"
#include <iostream>
#include "libraries/rapidxml/rapidxml.hpp"
#include <fstream>

using namespace rapidxml;
using namespace std;

Editor::Editor(Pointer* struct_pointer) : main_pointer(struct_pointer), current_zone(NULL){
    this->main_pointer->current_editor = this;
    createZone("Main");
    //std::cout << "finish object" << std::endl;
}

Editor::~Editor() {
    //delete current zones;
    for (int i=0; i< zone_array.size(); ++i) {
        delete zone_array[i];
    }
}

Editor* Editor::getEditor(){
    return this;
}

void Editor::createZone(){
    std::string base = "Zone";
    std::string name = "";
    char buffer[50];
    int i = 0;
    do{
        sprintf(buffer, "%d", i);
        name = base + buffer;
        i++;
    }while(this->isNameTaken(name));
    this->createZone(name.c_str());
}

void Editor::createZone(const char* name){
    std::string type = "ressources/form/";
    type += "group";
    type += ".obj";
    irr::scene::ISceneManager* scene = this->main_pointer->scene;
    irr::scene::ISceneNode* test = scene->addMeshSceneNode(scene->getMesh(type.c_str()));
    this->zone_array.push_back(new Zone(name, main_pointer, test));
    this->setCurrentZone(zone_array.size()-1);
    //current_zone = zone_array[zone_array.size()-1];
}

void Editor::setCurrentZone(Zone* zone){
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getPointer() == zone){
            if(zone != this->current_zone){
                setCurrentZone(i);
            }
        }
    }
}

void Editor::setCurrentZone(int index) {
    if(index >= 0 && index < this->zone_array.size()){
        if(this->current_zone != this->zone_array.at(index)){
            if(this->current_zone != NULL){
                this->setCurrentZoneVisible(false);
            }
            this->current_zone = this->zone_array.at(index);
            this->setCurrentZoneVisible(true);

            this->main_pointer->gui->updateZone(&this->zone_array);
            finishZoneSwitch();

        }
    }
}

Zone* Editor::getCurrentZone(){
    return this->current_zone;
}

void Editor::setMainPointer(Pointer* struct_pointer){
    main_pointer = struct_pointer;
}

void Editor::setCurrentZoneVisible(bool isVisible) {
    this->getCurrentZone()->getMeshPointer()->setVisible(isVisible);
    for(int i=0; i<this->getCurrentZone()->getGroupObjectVector()->size(); i++){
        this->getCurrentZone()->getGroupObjectVector()->at(i)->getSceneNode()->setVisible(isVisible);
    }
}

void Editor::finishZoneSwitch() {
    Zone* zone = this->current_zone;
    this->main_pointer->gui->updateGroupObject(zone->getGroupObjectVector());
    this->main_pointer->gui->updateSingleObject(zone->getSingleObjectVector());
    Object* objet = zone->getSelectedSingleObject();
    if(zone->getSelectedSingleObject() != NULL){
        zone->setSelectedSingleObject(zone->getSelectedSingleObject()->getSceneNode());
    }
    objet = zone->getSelectedGroupObject();
    if(zone->getSelectedGroupObject() != NULL){
        zone->setSelectedGroupObject(zone->getSelectedGroupObject()->getSceneNode());
    }
    this->main_pointer->gui->updateWindow();
    
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getPointer() == zone){
            this->main_pointer->gui->setZoneSelected(i);
        }
    }
}


Pointer* Editor::getMainPointer(){
    return main_pointer;
}

bool Editor::isNameTaken(std::string name){
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getName() == name){
            return true;
        }
    }
    return false;
}

void Editor::importData() {
    cout << "Start" << endl;
    xml_document<> doc;
    xml_node<> * root_node;
    // Read the xml file into a vector
    ifstream theFile ("save.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc 
    doc.parse<0>(&buffer[0]);
    // Find our root node
    root_node = doc.first_node("Editor");
    // Iterate over the brewerys
    for (xml_node<> * zone_node = root_node->first_node("Zone"); zone_node; zone_node = zone_node->next_sibling())
    {
        cout << zone_node->first_attribute("name")->value()<< endl;
        // Interate over the beers
        for(xml_node<> * object_node = zone_node->first_node("Object"); object_node; object_node = object_node->next_sibling())
        {
            for (xml_node<> * position_node = object_node->first_node("position"); position_node; position_node = position_node->next_sibling())
            {
                char * test = position_node->name();
                if(!strcmp(test, "position")){
                    cout << position_node->name() << endl;
                    cout << position_node->first_attribute("x")->value()<< endl;
                    cout << position_node->first_attribute("y")->value()<< endl;
                    cout << position_node->first_attribute("z")->value()<< endl;
                }

                else if(!strcmp(test, "rotation")){
                    cout << position_node->name() << endl;
                    cout << position_node->first_attribute("x")->value()<< endl;
                    cout << position_node->first_attribute("y")->value()<< endl;
                    cout << position_node->first_attribute("z")->value()<< endl;

                }

                else if(!strcmp(test, "scale")){
                    cout << position_node->name() << endl;
                    cout << position_node->first_attribute("x")->value()<< endl;
                    cout << position_node->first_attribute("y")->value()<< endl;
                    cout << position_node->first_attribute("z")->value()<< endl;
                }
            }
        }
        cout << endl;
    }
}

void Editor::importZone() {

}

void Editor::exportData(){
    TiXmlDocument doc;  
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
    doc.LinkEndChild( decl );  

    TiXmlElement * root = new TiXmlElement( "Editor" );  
    doc.LinkEndChild( root );  
    
    for(int i = 0; i < this->zone_array.size(); i++){
        zone_array.at(i)->exportZone(root);
    }
    doc.SaveFile( "save.xml" );  
} 