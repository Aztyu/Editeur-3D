/* 
 * File:   event.h
 * Author: Aztyu
 *
 * Created on 21 décembre 2014, 11:33
 */

#ifndef EVENT_H
#define	EVENT_H

#include <irrlicht.h>

#include "Zone.h"
 
class CEventReceiver : public irr::IEventReceiver{
 
    public :
        //Le constructeur.
        CEventReceiver(Zone* zone);
        //Capte automatiquement les events.
        virtual bool OnEvent(const irr::SEvent &event);
 
    private :
        //Le modele qu'on va controler.
        Zone* zone_actuelle;
};

#endif	/* EVENT_H */

