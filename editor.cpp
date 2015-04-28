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
    zone_array.push_back(new Zone(name, main_pointer));
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

