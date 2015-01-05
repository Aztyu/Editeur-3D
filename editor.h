/* 
 * File:   editor.h
 * Author: Aztyu
 *
 * Created on 26 décembre 2014, 11:29
 */

#ifndef EDITOR_H
#define	EDITOR_H

#include "Zone.h"
#include "Pointers.h"

class Editor {
    public:
        Editor(Zone* zone, Pointer* struct_pointer);
        Editor(const Editor& orig);
        virtual ~Editor();
        Editor* getEditor();
        void setCurrentZone(Zone* zone);
        Zone* getCurrentZone();
        void setMainPointer(Pointer* struct_pointer);
        Pointer* getMainPointer();
    private:
        std::vector<Zone*> zone_array;
        Zone* current_zone;
        Pointer* main_pointer;
};

#endif	/* EDITOR_H */

