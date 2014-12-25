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

class Zone {
public:
    Zone(irr::scene::ISceneManager* scn);
    Zone(char* name, irr::scene::ISceneManager* scn);
    Zone(const Zone& orig);
    virtual ~Zone();
    void addObjet(Objet* objet);
    void removeObjet(int index);
    void createObjet(object form);
    int getObjectCount();
    void printZone();
    Objet* getObjetPointer(int index);
    Zone* getPointer();
    
private:
    std::vector<Objet*> tableau;
    std::string zone_name;
    irr::scene::ISceneManager* scene;
};

#endif	/* ZONE_H */

