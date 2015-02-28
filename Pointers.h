/* 
 * File:   Pointers.h
 * Author: Aztyu
 *
 * Created on 31 décembre 2014, 09:39
 */

#ifndef POINTERS_H
#define	POINTERS_H

#include "irrlicht.h"

struct Pointer{     //Pointeur necessaire pour l'acces et le fonctionnement
    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* scene;
    irr::scene::ICameraSceneNode* camera;
    
    irr::gui::IGUIEnvironment* gui;
    irr::gui::IGUIComboBox* box_object;
};

#endif	/* POINTERS_H */

