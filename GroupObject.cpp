/* 
 * File:   GroupObject.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include "GroupObject.h"

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name): Object(obj, name){
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float total_scale, const char* name) : Object(obj, total_scale, name) {
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name) : Object(obj, x, y, z, name){
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name) : Object(obj, x, y, z, total_scale, name){
}

GroupObject::~GroupObject() {
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



