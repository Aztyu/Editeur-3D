/* 
 * File:   GroupObject.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include "GroupObject.h"

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name): Object(obj, name){
    this->objet->setVisible(0);
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float total_scale, const char* name) : Object(obj, total_scale, name) {
    this->objet->setVisible(0);
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name) : Object(obj, x, y, z, name){
    this->objet->setVisible(0);
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name) : Object(obj, x, y, z, total_scale, name){
    this->objet->setVisible(0);
}

GroupObject::~GroupObject() {
    //this->objet->remove();
}

void GroupObject::selectObject() {

}

void GroupObject::unselectObject() {

}

const char* GroupObject::printObjet() {
    return "test";
}



