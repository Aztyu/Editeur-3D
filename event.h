/* 
 * File:   event.h
 * Author: Aztyu
 *
 * Created on 21 décembre 2014, 11:33
 */

#ifndef EVENT_H
#define	EVENT_H

#include "Editor.h"
 
class CEventReceiver : public irr::IEventReceiver{
 
    public:
        CEventReceiver(Editor* editor);
        virtual bool OnEvent(const irr::SEvent &event);
        void OnObjectSelected(irr::gui::IGUIComboBox* combo);
        void OnMenuItemSelected(irr::gui::IGUIContextMenu* menu);
        void OnToolBoxItemSelected(irr::s32 id);
        void OnObjectCreation(irr::s32 id);
        
        void angleCameraRight();
        void angleCameraLeft();
        void forwardCamera();
        void backwardCamera();
        
    private:
        Editor* current_editor;
        GraphicalInterface* custom_gui;
};

#endif	/* EVENT_H */

