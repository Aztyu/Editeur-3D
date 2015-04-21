/* 
 * File:   Pointers.h
 * Author: Aztyu
 *
 * Created on 31 décembre 2014, 09:39
 */

#ifndef POINTERS_H
#define	POINTERS_H

//#include "irrlicht.h"
#include "GraphicalInterface.h"

struct Pointer{     //Pointeur necessaire pour l'acces et le fonctionnement
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* scene;
    irr::scene::ICameraSceneNode* camera; 
    GraphicalInterface* gui;
};

#endif	/* POINTERS_H */

