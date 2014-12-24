/* 
 * File:   Cube.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 18:25
 */

#include "Cube.h"
#include "Objet.h"

using namespace std; 

Cube::Cube() : Objet(), cote_cube(10) {
}

Cube::Cube(int cote) : Objet() {
    cote_cube = cote;
}

Cube::Cube(int posX, int posY, int posZ, int cote) : Objet(posX, posY, posZ) {
    cote_cube = cote;
}

Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

void Cube::printObjet(){
    cout << "Le cube se trouve en " << posX << posY << posZ << "et fait" << cote_cube << "de cote" << endl;
}

Cube* Cube::getPointer(){
    return this;
}

