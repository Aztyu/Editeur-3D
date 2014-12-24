/* 
 * File:   event.h
 * Author: Aztyu
 *
 * Created on 21 décembre 2014, 11:33
 */

#ifndef EVENT_H
#define	EVENT_H

#include <irrlicht.h>
 
class CEventReceiver : public irr::IEventReceiver
{
 
public :
 
    //Le constructeur.
    CEventReceiver(irr::scene::IAnimatedMeshSceneNode* Nmodele);
    
    //Capte automatiquement les events.
    virtual bool OnEvent(const irr::SEvent &event);
    //Met a jour la position du mesh.
    
    void majPosMesh();
 
 
private :
 
    //Le modele qu'on va controler.
    irr::scene::IAnimatedMeshSceneNode* m_Nmodele;
    
    //Indique si on est deja en mouvement ou pas.
    bool m_isMoving;
};

#endif	/* EVENT_H */

