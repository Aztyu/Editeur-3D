/* 
 * File:   Object.h
 * Author: Aztyu
 *
 * Created on 21 avril 2015, 17:07
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <iostream>
#include "irrlicht.h"

class Object {
public:
    Object(irr::scene::ISceneNode* objet, const char* name);
    Object(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    Object(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    Object(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);
    virtual ~Object();
    
    void setPosition(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void modifyPositionBy(float x, float y, float z);
    void modifyScaleBy(float x, float y, float z);
    void modifyRotationBy(float x, float y, float z);
    irr::scene::ISceneNode* getSceneNode();
    std::string getName();
    
protected:
    irr::scene::ISceneNode* objet;
    std::string object_name;
};

#endif	/* OBJECT_H */

