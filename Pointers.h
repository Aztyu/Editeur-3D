/* 
 * File:   Pointers.h
 * Author: Aztyu
 *
 * Created on 31 décembre 2014, 09:39
 */

#ifndef POINTERS_H
#define	POINTERS_H

#include "GraphicalInterface.h"

//! Pointeurs necessaire pour l'acces et le fonctionnement dans le programme entier
struct Pointer{
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* scene;
    irr::scene::ICameraSceneNode* camera; 
    GraphicalInterface* gui;
};

#endif	/* POINTERS_H */

