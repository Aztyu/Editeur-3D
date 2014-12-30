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
 
    public :
        CEventReceiver(Editor* editor);
        virtual bool OnEvent(const irr::SEvent &event);
 
    private :
        //Le modele qu'on va controler.
        Editor* editeur_actuelle;
};

#endif	/* EVENT_H */

