/* 
 * File:   editor.h
 * Author: Aztyu
 *
 * Created on 26 décembre 2014, 11:29
 */

#ifndef EDITOR_H
#define	EDITOR_H

#include "Zone.h"

//! Classe de base qui contient toutes les zones et la plupart des informations
class Editor {
    public:
        Editor(Pointer* struct_pointer);
        virtual ~Editor();
        
        //Gestion des zones
        void createZone(char* name);
        void setCurrentZone(Zone* zone);
        void setMainPointer(Pointer* struct_pointer);
        
        //Recuperation d'informations
        Pointer* getMainPointer();
        Editor* getEditor();
        Zone* getCurrentZone();
        
    private:
        std::vector<Zone*> zone_array;
        Zone* current_zone;
        Pointer* main_pointer;
};

#endif	/* EDITOR_H */

