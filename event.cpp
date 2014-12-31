#include "event.h"
 
CEventReceiver::CEventReceiver(Editor* editor){
    current_editor = editor;
}
 
bool CEventReceiver::OnEvent(const irr::SEvent &event){
    //On verifie que le pointeur est ok
    if(current_editor != 0){
        if(event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == true){
            irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
            irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
            irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
            irr::core::vector3df direction;
            irr::core::vector3df direction_mvnt;

            switch(event.KeyInput.Key){
                case irr::KEY_KEY_O:
                    rotation.X -= 10;
                    current_editor->getMainPointer()->camera->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_L:
                    rotation.X += 10;
                    current_editor->getMainPointer()->camera->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_A:
                    rotation.Y -= 10;
                    current_editor->getMainPointer()->camera->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_D:
                    rotation.Y += 10;
                    current_editor->getMainPointer()->camera->setRotation(rotation);
                    return true;

                case irr::KEY_KEY_W:  
                    direction_mvnt.X = target.X - position.X;
                    direction_mvnt.Y = 0;
                    direction_mvnt.Z = target.Z - position.Z;

                    direction_mvnt.normalize();
                    direction.X = 5*cos(acos(direction.X));
                    direction.Z = 5*sin(asin(direction.Z));

                    position.X += direction_mvnt.X;
                    position.Z += direction_mvnt.Z;

                    target.X += direction_mvnt.X;
                    target.Z += direction_mvnt.Z;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);
                    current_editor->getMainPointer()->camera->setTarget(target);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(true);
                    return true;
                    
                case irr::KEY_KEY_S:
                    direction_mvnt.X = target.X - position.X;
                    direction_mvnt.Y = 0;
                    direction_mvnt.Z = target.Z - position.Z;

                    direction_mvnt.normalize();
                    direction.X = 5*cos(acos(direction.X));
                    direction.Z = 5*sin(asin(direction.Y));

                    position.X -= direction_mvnt.X;
                    position.Z -= direction_mvnt.Z;


                    target.X -= direction_mvnt.X;
                    target.Z -= direction_mvnt.Z;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);
                    current_editor->getMainPointer()->camera->setTarget(target);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(true);
                    return true;

                case irr::KEY_KEY_I:
                    position.Y += 5;
                    target.Y += 5;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);
                    current_editor->getMainPointer()->camera->setTarget(target);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(true);
                    return true;
                    
                case irr::KEY_KEY_K:  
                    position.Y -= 5;
                    target.Y -= 5;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);
                    current_editor->getMainPointer()->camera->setTarget(target);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(true);
                    return true;
            }
        }
        
        if (event.EventType == irr::EET_GUI_EVENT)
        {
            irr::s32 id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType)
            {
                case irr::gui::EGET_BUTTON_CLICKED:
                    irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
                    irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
                    irr::core::vector3df direction;
                    irr::core::vector3df direction_mvnt;
                    
                    direction_mvnt.X = target.X - position.X;
                    direction_mvnt.Y = 0;
                    direction_mvnt.Z = target.Z - position.Z;

                    direction_mvnt.normalize();
                    direction.X = 18*cos(acos(direction_mvnt.X));
                    direction.Z = 18*sin(asin(direction_mvnt.Z));

                    position.X += direction.X;
                    position.Z += direction.Z;
                    position.Y = 0;
                    
                    switch(id){
                        case GUI_ID_SQUARE:
                            current_editor->getCurrentZone()->createObjet(cube);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_SPHERE:
                            current_editor->getCurrentZone()->createObjet(sphere);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_PYRAMID:
                            current_editor->getCurrentZone()->createObjet(pyramid);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                    }
                    break;   
            }
        }
    }
    return false;
}
 

