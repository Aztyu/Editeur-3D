/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include "SingleObjet.h"
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
    

class Zone {
    public:
        Zone(char* name, Pointer* pointer);
        Zone(const Zone& orig);
        virtual ~Zone();
        void addObjet(SingleObjet* objet);
        void removeObjet(int index);
        void removeObjet(SingleObjet* objet);
        void createObjet(object form);
        int getObjectCount();
        void printZone();
        SingleObjet* getObjetPointer(int index);
        SingleObjet* getSelectedObjet();
        Zone* getPointer();
        void setSelectedObject(int index);
        void setSelectedObject(irr::scene::ISceneNode* objet);
        void exportZone();

    private:
        std::vector<SingleObjet*> tableau;
        SingleObjet* selected_object;
        Pointer* current_pointer;
        std::string zone_name;
        int type_number[8];
};


#endif	/* ZONE_H */

