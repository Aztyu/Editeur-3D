/* 
 * File:   Object.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include <cmath>

#include "Object.h"

using namespace std;

Object::Object(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent) : object_name(name){
    objet = obj;        //Stock le pointeur vers le node
    objet->setPosition(irr::core::vector3df(0, 0, 0));
    this->default_parent = parent;
}

Object::Object(irr::scene::ISceneNode* obj, float total_scale, const char* name, irr::scene::ISceneNode* parent) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(0, 0, 0));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
    this->default_parent = parent;
}

Object::Object(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name, irr::scene::ISceneNode* parent) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
    this->default_parent = parent;
}

Object::Object(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name, irr::scene::ISceneNode* parent) : object_name(name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
    this->default_parent = parent;
}

Object::~Object() {
    //objet->remove();        //Suppression de l'objet dans irrlicht
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

void Object::modifyPositionBy(irr::core::vector3df values) {
    this->objet->setPosition(values + this->objet->getPosition());
}


void Object::modifyScaleBy(float x, float y, float z){
    irr::core::vector3df scale = objet->getScale();
    
    if(x > 0){
        scale.X *= x;
    }else if(x < 0){
        scale.X /= abs(x);
    }
    
    if(y > 0){
        scale.Y *= y;
    }else if(y < 0){
        scale.Y /= abs(y);
    }
    
    if(z > 0){
        scale.Z *= z;
    }else if(z < 0){
        scale.Z /= abs(z);
    }
    
    objet->setScale(scale);
}

void Object::modifyScaleBy(irr::core::vector3df values) {
    irr::core::vector3df scale = objet->getScale();
    
    if(values.X > 0){
        scale.X *= values.X;
    }else if(values.X < 0){
        scale.X /= std::abs(values.X);
    }
    
    if(values.Y > 0){
        scale.Y *= values.Y;
    }else if(values.Y < 0){
        scale.Y /= std::abs(values.Y);
    }
    
    if(values.Z > 0){
        scale.Z *= values.Z;
    }else if(values.Z < 0){
        scale.Z /= abs(values.Z);
    }
    
    objet->setScale(scale);
}


void Object::modifyRotationBy(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z) + objet->getRotation());
}

void Object::modifyRotationBy(irr::core::vector3df values) {
    objet->setRotation(values + objet->getRotation());
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

