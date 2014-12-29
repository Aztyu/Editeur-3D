/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include <vector>
#include "Objet.h"

enum object {
    rectangle,
    line,
    circle,
    trapeze,
    cube,
    pyramid,
    sphere,
    cylinder};
    
enum
{
    GUI_ID_SQUARE,
    GUI_ID_SPHERE,
    GUI_ID_PYRAMID
};

class Zone {
    public:
        Zone(irr::scene::ISceneManager* scn, irr::IrrlichtDevice* device);
        Zone(char* name, irr::scene::ISceneManager* scn, irr::IrrlichtDevice* device);
        Zone(const Zone& orig);
        virtual ~Zone();
        void addObjet(Objet* objet);
        void removeObjet(int index);
        void createObjet(object form);
        int getObjectCount();
        void printZone();
        Objet* getObjetPointer(int index);
        Zone* getPointer();
        irr::scene::ICameraSceneNode* getCamerapointer();
        irr::IrrlichtDevice* getDevicepointer();

    private:
        std::vector<Objet*> tableau;
        std::string zone_name;
        irr::scene::ISceneManager* scene;
        irr::scene::ICameraSceneNode *current_camera;
        irr::IrrlichtDevice* current_device;
};


#endif	/* ZONE_H */

