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
    object_name = name; //Stocke le nom
    objet->setPosition(irr::core::vector3df(0, 0, 0));
}

Objet::Objet(irr::scene::ISceneNode* obj, float total_scale, const char* name) {
    objet = obj;
    objet->setPosition(irr::core::vector3df(0, 0, 0));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
    object_name = name;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
    object_name = name;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name){
    objet = obj;
    object_name = name;
    objet->setPosition(irr::core::vector3df(x, y, z));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
}

Objet::Objet(const Objet& orig) {
}

Objet::~Objet() {
    objet->remove();
    cout << "Object deleted" << endl;
}

void Objet::printObjet(){
    //cout << "L'objet se trouve en " << position.X  << position.Y << position.Z << "et a pour " << objet << endl;
}

void Objet::setPosition(float x, float y, float z){

    objet->setPosition(irr::core::vector3df(x, y, z));
}

void Objet::setScale(float x, float y, float z){
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

