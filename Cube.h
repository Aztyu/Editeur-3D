/* 
 * File:   Cube.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 18:25
 */

#ifndef CUBE_H
#define	CUBE_H

#include "Objet.h"

class Cube : public Objet {
public:
    Cube();
    Cube(int cote); 
    Cube(int posX, int posY, int posZ, int cote);
    Cube(const Cube& orig);
    virtual ~Cube();
    void printObjet();
    Cube* getPointer();
private:
    int cote_cube;
};

#endif	/* CUBE_H */

