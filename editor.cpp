/* 
 * File:   editor.cpp
 * Author: Aztyu
 * 
 * Created on 26 décembre 2014, 11:29
 */

#include "editor.h"
#include "event.h"

Editor::Editor(Zone* zone, Pointer* struct_pointer) {
    main_pointer = struct_pointer;
    current_zone = zone;
    std::cout << "finish object" << std::endl;
}

Editor::Editor(const Editor& orig) {
}

Editor::~Editor() {
}

Editor* Editor::getEditor(){
    return this;
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