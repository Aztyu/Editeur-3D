/* 
 * File:   Objet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "Objet.h"

using namespace std;

Objet::Objet(irr::scene::ISceneNode* obj, const char* name) {
    objet = obj;        //Stock le pointeur vers le node
    position.X = 0;
    position.Y = 0;
    position.Z = 0;
    scale.X = 1.0;
    scale.Y = 1.0;
    scale.Z = 1.0;
    object_name = name; //Stocke le nom
}

Objet::Objet(irr::scene::ISceneNode* obj, float total_scale, const char* name) {
    objet = obj;
    position.X = 0;
    position.Y = 0;
    position.Z = 0; 
    scale.X = total_scale;
    scale.Y = total_scale;
    scale.Z = total_scale;
    object_name = name;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name){
    objet = obj;
    position.X = x;
    position.Y = y;
    position.Z = z; 
    scale.X = 1.0;
    scale.Y = 1.0;
    scale.Z = 1.0;
    object_name = name;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name){
    objet = obj;
    position.X = x;
    position.Y = y;
    position.Z = z;
    scale.X = total_scale;
    scale.Y = total_scale;
    scale.Z = total_scale;
    object_name = name;
}

Objet::Objet(const Objet& orig) {
}

Objet::~Objet() {
    cout << "Object deleted" << endl;
}

void Objet::printObjet(){
    cout << "L'objet se trouve en " << position.X  << position.Y << position.Z << "et a pour " << objet << endl;
}

void Objet::setPosition(float x, float y, float z){
    position.X = x;
    position.Y = y;
    position.Z = z;
    objet->setPosition(irr::core::vector3df(x, y, z));
}

void Objet::setScale(float x, float y, float z){
    scale.X = x;
    scale.Y = y;
    scale.Z = z;
    objet->setScale(irr::core::vector3df(x, y, z));
}

void Objet::setRotation(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z));
}

void Objet::setParent(Objet* parent){  //Utile pour la creation de groupe 
    objet->setParent(parent->getSceneNode());
}

Objet* Objet::getPointer(){
    return this;
}

irr::scene::ISceneNode* Objet::getSceneNode(){  //Retourne le pointeur vers le node
    return objet;
}

