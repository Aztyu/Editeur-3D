/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

#include <iostream>
#include "irrlicht.h"

class SingleObjet {
public:
    SingleObjet(irr::scene::ISceneNode* objet, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);
    SingleObjet(const SingleObjet& objetACopier);
    virtual ~SingleObjet();
    
    friend std::ostream& operator <<(std::ostream stream, SingleObjet& obj);
    const char* printObjet();
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void modifyPositionBy(float x, float y, float z);
    void modifyScaleBy(float x, float y, float z);
    void modifyRotationBy(float x, float y, float z);
    void setParent(SingleObjet* parent);
    SingleObjet* getPointer();
    irr::scene::ISceneNode* getSceneNode();
    
protected:
    irr::scene::ISceneNode* objet;
    std::string object_name;
};

#endif	/* SINGLEOBJECT_H */

