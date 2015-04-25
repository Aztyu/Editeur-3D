/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include "Pointers.h"
#include "GroupObject.h"

enum object {
    rectangle,
    line,
    circle,
    trapeze,
    cube,
    pyramid,
    sphere,
    cylinder,
    group};
    

class Zone {
    
    public:
        Zone(char* name, Pointer* pointer);
        Zone(const Zone& orig);
        virtual ~Zone();
        void addObjet(SingleObjet* objet);
        void removeObjet(int index);
        void removeObjet(SingleObjet* objet);
        void createSingleObjet(object form);
        void createGroupObject();
        int getObjectCount();
        void printZone();
        SingleObjet* getSingleObjetPointer(int index);
        GroupObject* getGroupObjectPointer(int index);
        SingleObjet* getSelectedSingleObject();
        GroupObject* getSelectedGroupObject();
        Zone* getPointer();
        void setSelectedSingleObject(int index);
        void setSelectedSingleObject(irr::scene::ISceneNode* objet);
        void setSelectedGroupObject(int index);
        void unselectAll();
        void exportZone();

    private:
        std::vector<SingleObjet*> single_object_array; //Ne pas passer de pointer a objet ca fait tout peter
        std::vector<GroupObject*> group_object_array;
        SingleObjet* selected_object;
        GroupObject* selected_group;
        Pointer* current_pointer;
        std::string zone_name;
        int type_number[9];
};


#endif	/* ZONE_H */

