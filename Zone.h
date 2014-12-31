/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include "Objet.h"
#include "Pointers.h"
#include <vector>

enum object {
    rectangle,
    line,
    circle,
    trapeze,
    cube,
    pyramid,
    sphere,
    cylinder};
    
enum {
    GUI_ID_SQUARE,
    GUI_ID_SPHERE,
    GUI_ID_PYRAMID,
    GUI_ID_OBJECT
};

class Zone {
    public:
        Zone(char* name, Pointer* pointer);
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
        Pointer* current_pointer;
        std::string zone_name;
        int type_number[8];
};


#endif	/* ZONE_H */

