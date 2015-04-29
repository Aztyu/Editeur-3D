/* 
 * File:   editor.cpp
 * Author: Aztyu
 * 
 * Created on 26 décembre 2014, 11:29
 */

#include "Editor.h"
#include "Event.h"

Editor::Editor(Pointer* struct_pointer) : main_pointer(struct_pointer) {
    createZone("Main");
    this->main_pointer->current_editor = this;
    current_zone = zone_array[zone_array.size()-1];
    std::cout << "finish object" << std::endl;
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

void Editor::createZone(char* name){
    std::string type = "ressources/form/";
    type += "group";
    type += ".obj";
    //this->group_object_array.push_back(new GroupObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str()));        //Chargement et creation de l'objet
    irr::scene::ISceneManager* scene = this->main_pointer->scene;
    irr::scene::ISceneNode* test = scene->addMeshSceneNode(scene->getMesh(type.c_str()));
    this->zone_array.push_back(new Zone(name, main_pointer, test));
    current_zone = zone_array[zone_array.size()-1];
}

void Editor::setCurrentZone(Zone* zone){
    current_zone = zone;
}

Zone* Editor::getCurrentZone(){
    return current_zone;
}

void Editor::setMainPointer(Pointer* struct_pointer){
    main_pointer = struct_pointer;
}

Pointer* Editor::getMainPointer(){
    return main_pointer;
}

