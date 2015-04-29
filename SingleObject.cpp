/* 
 * File:   SingleObjet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "SingleObject.h"

using namespace std;

SingleObject::SingleObject(irr::scene::ISceneNode* obj, const char* name): Object(obj, name){}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float total_scale, const char* name) : Object(obj, total_scale, name) {}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name) : Object(obj, x, y, z, name){}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name) : Object(obj, x, y, z, total_scale, name){
}

void SingleObject::selectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
}

void SingleObject::groupSelectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 248, 158, 37);
}

void SingleObject::unselectObject() {
    this->objet->getMaterial(0).EmissiveColor = 0;
}


std::ostream& operator <<(std::ostream& stream, SingleObject& obj){    //Completer pour l'export
    stream << obj.printObject();
    return stream;
}

const string SingleObject::printObject(){
    std::string obj_name = "L'objet se trouve en ";
    return obj_name;
}

void SingleObject::setParent(Object* parent){  //Utile pour la creation de groupe 
    objet->setParent(parent->getSceneNode());
}

bool SingleObject::hasParent() {
    return this->objet->getParent() != NULL;
}

SingleObject* SingleObject::getPointer(){
    return this;
}

