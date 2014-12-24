/* 
 * File:   Sphere.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 18:26
 */

#ifndef SPHERE_H
#define	SPHERE_H

#include "Objet.h"

class Sphere : public Objet{
public:
    Sphere();
    Sphere(int rayon); 
    Sphere(int posX, int posY, int posZ, int rayon);
    Sphere(const Sphere& orig);
    virtual ~Sphere();
    void printObjet();
    Sphere* getPointer();
private:
    int cercle_rayon;

};

#endif	/* SPHERE_H */

