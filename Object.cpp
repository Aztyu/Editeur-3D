/* 
 * File:   Object.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include "Object.h"

using namespace std;

Object::Object(irr::scene::ISceneNode* obj, const char* name) : object_name(name){
    objet = obj;        //Stock le pointeur vers le node
    objet->setPosition(irr::core::vector3df(0, 0, 0));
}

Object::Object(irr::scene::ISceneNode* obj, float total_scale, const char* name) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(0, 0, 0));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
}

Object::Object(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
}

Object::Object(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
}

Object::~Object() {
    objet->remove();        //Suppression de l'objet dans irrlicht
    cout << "Object deleted" << endl;
}

void Object::setPosition(float x, float y, float z){        //Methodes absolues
    objet->setPosition(irr::core::vector3df(x, y, z));
}

void Object::setScale(float x, float y, float z){
    objet->setScale(irr::core::vector3df(x, y, z));
}

void Object::setRotation(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z));
}

void Object::modifyPositionBy(float x, float y, float z){        //Methodes relatives, utilise la valeur de base plus celle que vous rajoutez
    objet->setPosition(irr::core::vector3df(x, y, z) + objet->getPosition());
}

void Object::modifyScaleBy(float x, float y, float z){
    objet->setScale(irr::core::vector3df(x, y, z) + objet->getScale());
}

void Object::modifyRotationBy(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z) + objet->getRotation());
}

const irr::core::vector3df& Object::getPosition() {
    return this->objet->getPosition();
}

const irr::core::vector3df& Object::getScale() {
    return this->objet->getScale();
}

const irr::core::vector3df& Object::getRotation() {
    return this->objet->getRotation();
}

irr::scene::ISceneNode* Object::getSceneNode(){  //Retourne le pointeur vers le node
    return objet;
}

std::string Object::getName() {
    return this->object_name;
}

