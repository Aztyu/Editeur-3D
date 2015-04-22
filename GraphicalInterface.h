/* 
 * File:   GraphicalInterface.h
 * Author: Aztyu
 *
 * Created on 19 avril 2015, 16:48
 */

#include "SingleObjet.h"

#ifndef GRAPHICALINTERFACE_H
#define	GRAPHICALINTERFACE_H

enum {                  //Ajoutez les ids utilises dans le GUI ici
    GUI_ID_SQUARE,
    GUI_ID_RECTANGLE,
    GUI_ID_LINE,
    GUI_ID_TRAPEZE,
    GUI_ID_SPHERE,
    GUI_ID_PYRAMID,
    GUI_ID_CIRCLE,
    GUI_ID_CYLINDER,
    GUI_ID_OBJECT
};

class GraphicalInterface {
public:
    GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver);
    //GraphicalInterface(const GraphicalInterface& orig);
    virtual ~GraphicalInterface();
    void drawAll();
    void updateSingleObject(std::vector<SingleObjet>* tableau);
    void setSingleObjetSelected(int index);
private:
    irr::gui::IGUIContextMenu* menu;
    irr::gui::IGUIComboBox* single_object_box;
    
    irr::video::IVideoDriver* driver;
    irr::gui::IGUIEnvironment* gui;
};

#endif	/* GRAPHICALINTERFACE_H */

