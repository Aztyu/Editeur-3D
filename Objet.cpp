/* 
 * File:   Objet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */

#include "Objet.h"

using namespace std;

Objet::Objet() : posX(0), posY(0), posZ(0) {
    cout <<  "Creation d'un objet en" << posX << posY << posZ << endl;
}

Objet::Objet(float x, float y, float z) : posX(x), posY(y), posZ(z) {
    cout <<  "Creation d'un objet en" << posX << posY << posZ << endl;
}

Objet::Objet(const Objet& orig) {
}

Objet::~Objet() {
}

void Objet::printObjet(){
    cout << "L'objet se trouve en " << posX << posY << posZ << endl;
}

void Objet::setPosition(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}

Objet* Objet::getPointer(){
    return this;
}

