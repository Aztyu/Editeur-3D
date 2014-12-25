/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef OBJET_H
#define	OBJET_H

#include <iostream>
#include "irrlicht.h"

class Objet {
public:
    Objet(irr::scene::ISceneNode* objet);
    Objet(irr::scene::ISceneNode* objet, float total_scale);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale);
    Objet(const Objet& objetACopier);
    virtual ~Objet();
    virtual void printObjet();
    void setPosition(float x, float y, float z);
    Objet* getPointer();
    
protected:
    irr::scene::ISceneNode* objet;
    irr::core::vector3df position;
    irr::core::vector3df scale;
};

#endif	/* OBJET_H */

