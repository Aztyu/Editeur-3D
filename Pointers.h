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
    irr::IrrlichtDevice* device;            /**< Pointeur vers le device d'Irrlicht. */
    irr::video::IVideoDriver* driver;       /**< Pointeur vers le driver d'Irrlicht. */
    irr::scene::ISceneManager* scene;       /**< Pointeur vers la scene d'Irrlicht. */
    irr::scene::ICameraSceneNode* camera;   /**< Pointeur vers la camera. */
    GraphicalInterface* gui;                /**< Pointeur vers l'objet GraphicalInterface. */
};

#endif	/* POINTERS_H */

