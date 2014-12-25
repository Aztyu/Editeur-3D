/* 
 * File:   Objet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "Objet.h"

using namespace std;

Objet::Objet(irr::scene::ISceneNode* obj) {
    objet = obj;
    position.X = 0;
    position.Y = 0;
    position.Z = 0;
    scale.X = 1.0;
    scale.Y = 1.0;
    scale.Z = 1.0;
}

Objet::Objet(irr::scene::ISceneNode* obj, float total_scale) {
    objet = obj;
    position.X = 0;
    position.Y = 0;
    position.Z = 0; 
    scale.X = total_scale;
    scale.Y = total_scale;
    scale.Z = total_scale;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z){
    objet = obj;
    position.X = x;
    position.Y = y;
    position.Z = z; 
    scale.X = 1.0;
    scale.Y = 1.0;
    scale.Z = 1.0;
}

Objet::Objet(irr::scene::ISceneNode* obj, float x, float y, float z, float total_scale){
    objet = obj;
    position.X = x;
    position.Y = y;
    position.Z = z;
    scale.X = total_scale;
    scale.Y = total_scale;
    scale.Z = total_scale;
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
}

Objet* Objet::getPointer(){
    return this;
}

