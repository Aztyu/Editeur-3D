/* 
 * File:   editor.cpp
 * Author: Aztyu
 * 
 * Created on 26 décembre 2014, 11:29
 */

#include "editor.h"
#include "event.h"

Editor::Editor(Pointer* struct_pointer) {
    main_pointer = struct_pointer;
    createZone("Main");
    std::cout << "finish object" << std::endl;
}

Editor::Editor(const Editor& orig) {
}

Editor::~Editor() {
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

