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
    Objet(irr::scene::ISceneNode* objet, const char* name);
    Objet(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);
    Objet(const Objet& objetACopier);
    virtual ~Objet();
    virtual void printObjet();
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setParent(Objet* parent);
    Objet* getPointer();
    irr::scene::ISceneNode* getSceneNode();
    
protected:
    irr::scene::ISceneNode* objet;
    std::string object_name;
};

#endif	/* OBJET_H */

