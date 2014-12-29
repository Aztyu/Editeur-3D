#include "event.h"
 
CEventReceiver::CEventReceiver(Zone* zone)
{
    zone_actuelle = zone;
}
 
 
bool CEventReceiver::OnEvent(const irr::SEvent &event)
{
    //On verifie que le pointeur est ok
    if(zone_actuelle != 0){
        if(event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == true){
            irr::core::vector3df position = zone_actuelle->getCamerapointer()->getPosition();
            irr::core::vector3df rotation = zone_actuelle->getCamerapointer()->getRotation();
            irr::core::vector3df target = zone_actuelle->getCamerapointer()->getTarget();
            irr::core::vector3df direction;
            irr::core::vector3df direction_mvnt;

            switch(event.KeyInput.Key){
                case irr::KEY_KEY_O:
                    rotation.X -= 10;
                    zone_actuelle->getCamerapointer()->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_L:
                    rotation.X += 10;
                    zone_actuelle->getCamerapointer()->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_A:
                    rotation.Y -= 10;
                    zone_actuelle->getCamerapointer()->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_D:
                    rotation.Y += 10;
                    zone_actuelle->getCamerapointer()->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_W:  
                    direction_mvnt.X = target.X - position.X;
                    direction_mvnt.Y = 0;
                    direction_mvnt.Z = target.Z - position.Z;

                    direction_mvnt.normalize();
                    direction.X = 5*cos(acos(direction.X));
                    direction.Y = 5*sin(asin(direction.Y));

                    position.X += direction_mvnt.X;
                    position.Z += direction_mvnt.Z;

                    target.X += direction_mvnt.X;
                    target.Z += direction_mvnt.Z;

                    zone_actuelle->getCamerapointer()->setPosition(position);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(false);
                    zone_actuelle->getCamerapointer()->setTarget(target);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(true);
                    return true;
                    
                case irr::KEY_KEY_S:
                    direction_mvnt.X = target.X - position.X;
                    direction_mvnt.Y = 0;
                    direction_mvnt.Z = target.Z - position.Z;

                    direction_mvnt.normalize();
                    direction.X = 5*cos(acos(direction.X));
                    direction.Y = 5*sin(asin(direction.Y));

                    position.X -= direction_mvnt.X;
                    position.Z -= direction_mvnt.Z;


                    target.X -= direction_mvnt.X;
                    target.Z -= direction_mvnt.Z;

                    zone_actuelle->getCamerapointer()->setPosition(position);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(false);
                    zone_actuelle->getCamerapointer()->setTarget(target);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(true);
                    return true;

                case irr::KEY_KEY_I:
                    position.Y += 5;
                    target.Y += 5;

                    zone_actuelle->getCamerapointer()->setPosition(position);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(false);
                    zone_actuelle->getCamerapointer()->setTarget(target);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(true);
                    return true;
                    
                case irr::KEY_KEY_K:  
                    position.Y -= 5;
                    target.Y -= 5;

                    zone_actuelle->getCamerapointer()->setPosition(position);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(false);
                    zone_actuelle->getCamerapointer()->setTarget(target);
                    zone_actuelle->getCamerapointer()->bindTargetAndRotation(true);
                    return true;
            }
        }
        
        if (event.EventType == irr::EET_GUI_EVENT)
        {
            irr::s32 id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType)
            {
                case irr::gui::EGET_BUTTON_CLICKED:
                    irr::core::vector3df position = zone_actuelle->getCamerapointer()->getTarget();
                    position.Y = 0;
                    
                    switch(id){
                        case GUI_ID_SQUARE:
                            zone_actuelle->createObjet(cube);
                            zone_actuelle->getObjetPointer(zone_actuelle->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_SPHERE:
                            zone_actuelle->createObjet(sphere);
                            zone_actuelle->getObjetPointer(zone_actuelle->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_PYRAMID:
                            zone_actuelle->createObjet(pyramid);
                            zone_actuelle->getObjetPointer(zone_actuelle->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                    }
                    break;   
            }
        }
    }
    return false;
}
 

