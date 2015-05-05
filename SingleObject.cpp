/* 
 * File:   SingleObjet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "SingleObject.h"
#include "GroupObject.h"

using namespace std;

SingleObject::SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent): Object(obj, name, parent){
    this->parent = NULL;
}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float total_scale, const char* name, irr::scene::ISceneNode* parent) : Object(obj, total_scale, name, parent) {
    this->parent = NULL;
}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name, irr::scene::ISceneNode* parent) : Object(obj, x, y, z, name, parent){
    this->parent = NULL;
}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name, irr::scene::ISceneNode* parent) : Object(obj, x, y, z, total_scale, name, parent){
    this->parent = NULL;
}

SingleObject::~SingleObject() {
    if(parent != NULL){
        static_cast<GroupObject*>(parent)->removeMember(this);
    }
    this->objet->remove();        //Suppression de l'objet dans irrlicht
    cout << "Object deleted" << endl;
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

void SingleObject::setParent(Object* parent){
    if(parent == NULL){
        this->objet->setParent(this->default_parent);
        this->parent = NULL;
    }else{
        objet->setParent(parent->getSceneNode());
        this->parent = parent;
    }
}

bool SingleObject::hasParent() {
    return this->parent != NULL;
}

SingleObject* SingleObject::getPointer(){
    return this;
}

