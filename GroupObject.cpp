/* 
 * File:   GroupObject.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include "GroupObject.h"

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent): Object(obj, name, parent){
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float total_scale, const char* name, irr::scene::ISceneNode* parent) : Object(obj, total_scale, name, parent) {
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name, irr::scene::ISceneNode* parent) : Object(obj, x, y, z, name, parent){
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name, irr::scene::ISceneNode* parent) : Object(obj, x, y, z, total_scale, name, parent){
}

GroupObject::~GroupObject() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->setParent(NULL);
    }
    this->unselectObject();
    this->objet->remove();        //Suppression de l'objet dans irrlicht
    std::cout << "Object deleted" << std::endl;
}

void GroupObject::selectObject() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->groupSelectObject();
    }
}

void GroupObject::unselectObject() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->unselectObject();
    }
}

void GroupObject::addMember(SingleObject* object) {
    this->member_object.push_back(object);
    object->setParent(this);
}

void GroupObject::removeMember(int index) {
    if(index >= 0 && index < this->member_object.size()){
        if(this->member_object[index] != NULL){
            this->member_object[index]->setParent(NULL);
            this->member_object.erase(this->member_object.begin()+index);
        }
    }
}

void GroupObject::removeMember(SingleObject* object) {
    for(int i = 0;i<this->member_object.size(); ++i){
        if(object == this->member_object[i]){
            this->removeMember(i);
            return;
        }
    }
}



const char* GroupObject::printObject() {
    return "test";
}



