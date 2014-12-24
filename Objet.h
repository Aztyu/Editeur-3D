/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef OBJET_H
#define	OBJET_H

#include <iostream>

class Objet {
public:
    Objet();
    Objet(float x, float y, float z);
    Objet(const Objet& objetACopier);
    virtual ~Objet();
    virtual void printObjet();
    void setPosition(float x, float y, float z);
    Objet* getPointer();
    
protected:
    float posX;
    float posY;
    float posZ;
};

#endif	/* OBJET_H */

