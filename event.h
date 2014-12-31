/* 
 * File:   event.h
 * Author: Aztyu
 *
 * Created on 21 décembre 2014, 11:33
 */

#ifndef EVENT_H
#define	EVENT_H

#include "editor.h"
 
class CEventReceiver : public irr::IEventReceiver{
 
    public:
        CEventReceiver(Editor* editor);
        virtual bool OnEvent(const irr::SEvent &event);
        void OnObjectSelected(irr::gui::IGUIComboBox* combo);
    private:
        Editor* current_editor;
};

#endif	/* EVENT_H */

