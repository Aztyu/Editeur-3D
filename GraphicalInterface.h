/* 
 * File:   GraphicalInterface.h
 * Author: Aztyu
 *
 * Created on 19 avril 2015, 16:48
 */

#include "SingleObjet.h"
#include "GroupObject.h"

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
    
    GUI_ID_SINGLE_OBJECT_COMBO_BOX,
    GUI_ID_GROUP_OBJECT_COMBO_BOX,
    
    GUI_ID_OBJECT_WINDOW,
    
    GUI_ID_FILE,
    GUI_ID_SETTINGS,
    GUI_ID_HELP,
    GUI_ID_NEW,
    GUI_ID_LOAD,
    GUI_ID_SAVE,
    GUI_ID_QUIT,
    GUI_ID_SKYBOX,
    GUI_ID_TOOLBOX,
    GUI_ID_DOC,
    GUI_ID_ABOUT
};

class GraphicalInterface {
public:
    GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver);
    virtual ~GraphicalInterface();
    void drawAll();
    void updateSingleObject(std::vector<SingleObjet*>* tableau);
    void setSingleObjetSelected(int index);
    void updateGroupObject(std::vector<GroupObject*>* tableau);
    void setGroupObjetSelected(int index);
    irr::gui::IGUIEnvironment* getGUIEnvironment();
    void updateWindow(Object* object = NULL);
    
private:
    irr::gui::IGUIContextMenu* menu;
    irr::gui::IGUIComboBox* single_object_box;
    irr::gui::IGUIComboBox* group_object_box;
    
    irr::video::IVideoDriver* driver;
    irr::gui::IGUIEnvironment* gui;
};

#endif	/* GRAPHICALINTERFACE_H */

