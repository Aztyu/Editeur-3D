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

class Zone {
public:
    Zone();
    Zone(char* name);
    Zone(const Zone& orig);
    virtual ~Zone();
    void addObjet(Objet* objet);
    int getObjectCount();
    void printZone();
    Objet* getObjetPointer(int index);
    
private:
    std::vector<Objet*> tableau;
    std::string zone_name;
};

#endif	/* ZONE_H */

