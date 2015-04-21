/* 
 * File:   SingleObjet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "SingleObjet.h"

using namespace std;

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, const char* name) {
    objet = obj;        //Stock le pointeur vers le node
    object_name = name; //Stocke le nom
    objet->setPosition(irr::core::vector3df(0, 0, 0));
}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float total_scale, const char* name) {
    objet = obj;
    objet->setPosition(irr::core::vector3df(0, 0, 0));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
    object_name = name;
}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float x, float y, float z, const char* name){
    objet = obj;
    objet->setPosition(irr::core::vector3df(x, y, z));
    object_name = name;
}

SingleObjet::SingleObjet(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale, const char* name){
    objet = obj;
    object_name = name;
    objet->setPosition(irr::core::vector3df(x, y, z));
    objet->setScale(irr::core::vector3df(total_scale, total_scale, total_scale));
}

SingleObjet::SingleObjet(const SingleObjet& orig) {
}

SingleObjet::~SingleObjet() {
    objet->remove();        //Suppression de l'objet dans irrlicht
    cout << "Object deleted" << endl;
}

std::ostream& operator <<(std::ostream& stream, SingleObjet& obj){    //Completer pour l'export
    stream << obj.printObjet();
    return stream;
}

const char* SingleObjet::printObjet(){
    std::string obj_name = "L'objet se trouve en ";
    return obj_name.c_str();
}

void SingleObjet::setPosition(float x, float y, float z){        //Methodes absolues
    objet->setPosition(irr::core::vector3df(x, y, z));
}

void SingleObjet::setScale(float x, float y, float z){
    objet->setScale(irr::core::vector3df(x, y, z));
}

void SingleObjet::setRotation(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z));
}

void SingleObjet::modifyPositionBy(float x, float y, float z){        //Methodes relatives, utilise la valeur de base plus celle que vous rajoutez
    objet->setPosition(irr::core::vector3df(x, y, z) + objet->getPosition());
}

void SingleObjet::modifyScaleBy(float x, float y, float z){
    objet->setScale(irr::core::vector3df(x, y, z) + objet->getScale());
}

void SingleObjet::modifyRotationBy(float x, float y, float z){
    objet->setRotation(irr::core::vector3df(x, y, z) + objet->getRotation());
}

void SingleObjet::setParent(SingleObjet* parent){  //Utile pour la creation de groupe 
    objet->setParent(parent->getSceneNode());
}

SingleObjet* SingleObjet::getPointer(){
    return this;
}

irr::scene::ISceneNode* SingleObjet::getSceneNode(){  //Retourne le pointeur vers le node
    return objet;
}

std::string SingleObjet::getName() {
    return this->object_name;
}

