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

irr::IrrlichtDevice* current_device = 0;
irr::video::IVideoDriver* current_driver = 0;
irr::gui::IGUIEnvironment* current_gui = 0;
irr::scene::ICameraSceneNode* current_camera = 0;
irr::scene::ISceneManager* current_scene = 0;

class Objet {
public:
    Objet(irr::scene::ISceneNode* objet, char* name);
    Objet(irr::scene::ISceneNode* objet, float total_scale, char* name);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z, char* name);
    Objet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, char* name);
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
    irr::core::vector3df position;
    irr::core::vector3df scale;
};

#endif	/* OBJET_H */

