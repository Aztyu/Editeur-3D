/* 
 * File:   SingleObjet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "SingleObjet.h"

using namespace std;

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, const char* name): Object(obj, name){}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float total_scale, const char* name) : Object(obj, total_scale, name) {}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name) : Object(obj, x, y, z, name){}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name) : Object(obj, x, y, z, total_scale, name){
}

void SingleObjet::selectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
}

void SingleObjet::groupSelectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 248, 158, 37);
}

void SingleObjet::unselectObject() {
    this->objet->getMaterial(0).EmissiveColor = 0;
}


std::ostream& operator <<(std::ostream& stream, SingleObjet& obj){    //Completer pour l'export
    stream << obj.printObjet();
    return stream;
}

const char* SingleObjet::printObjet(){
    std::string obj_name = "L'objet se trouve en ";
    return obj_name.c_str();
}

void SingleObjet::setParent(Object* parent){  //Utile pour la creation de groupe 
    objet->setParent(parent->getSceneNode());
}

bool SingleObjet::hasParent() {
    return this->objet->getParent() != NULL;
}

SingleObjet* SingleObjet::getPointer(){
    return this;
}

