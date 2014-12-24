/* 
 * File:   Sphere.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 18:26
 */

#include "Sphere.h"
#include "Objet.h"

using namespace std;

Sphere::Sphere() : cercle_rayon(10){
}

Sphere::Sphere(int rayon) : Objet() {
    cercle_rayon = rayon;
}

Sphere::Sphere(int posX, int posY, int posZ, int rayon) : Objet(posX, posY, posZ) {
    cercle_rayon = rayon;
}

Sphere::Sphere(const Sphere& orig) {
}

Sphere::~Sphere() {
}

void Sphere::printObjet(){
    cout << "La sphere se trouve en " << posX << posY << posZ << "et a un rayon de" << cercle_rayon << endl;
}

Sphere* Sphere::getPointer(){
    return this;
}

