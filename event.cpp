#include "Event.h"
 
CEventReceiver::CEventReceiver(Editor* editor){
    current_editor = editor;
}
 
bool CEventReceiver::OnEvent(const irr::SEvent &event){
    if(current_editor != 0){            //On verifie que le pointeur est ok
        if(event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == true){
            irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
            irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
            irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
            irr::core::vector3df direction;
            irr::core::vector3df direction_mvnt;

            switch(event.KeyInput.Key){
                case irr::KEY_RETURN: //Maj de la scale suite a l'appui d'entree, exemple recupere dans la doc irrlicht
                    /* set scale
                    irr::gui::IGUIElement* root = env->getRootGUIElement();
                    irr::core::vector3df scale;
                    irr::core::stringc s;

                    s = root->getElementFromId(GUI_ID_X_SCALE, true)->getText();
                    scale.X = (irr::f32)atof(s.c_str());
                    s = root->getElementFromId(GUI_ID_Y_SCALE, true)->getText();
                    scale.Y = (irr::f32)atof(s.c_str());
                    s = root->getElementFromId(GUI_ID_Z_SCALE, true)->getText();
                    scale.Z = (irr::f32)atof(s.c_str());

                    if (Model)
                        Model->setScale(scale);
                    updateScaleInfo(Model);*/
                    return true;
                
                case irr::KEY_ESCAPE:  //Ferme le programme
                    current_editor->getMainPointer()->device->closeDevice();
                    return true;
                    
                case irr::KEY_DELETE:  //Supprime l'objet selectionne
                    current_editor->getCurrentZone()->removeObjet(current_editor->getCurrentZone()->getSelectedObjet());
                    return true;
                    
                case irr::KEY_KEY_O:  //Camera vers le haut
                    if(rotation.X > -80){
                        rotation.X -= 10;
                        current_editor->getMainPointer()->camera->setRotation(rotation);
                    }
                    return true;

                case irr::KEY_KEY_L:  //Camera vers le bas
                    if(rotation.X < 80){
                        rotation.X += 10;
                        current_editor->getMainPointer()->camera->setRotation(rotation);
                    }
                    return true;

                case irr::KEY_KEY_Q:  //Camera vers la gauche
                    angleCameraRight();
                    return true;

                case irr::KEY_KEY_D:  //Camera vers la droite
                    angleCameraLeft();
                    return true;

                case irr::KEY_KEY_Z:  //Camera avance
                    forwardCamera();
                    return true;
                    
                case irr::KEY_KEY_S:  //Camera recule
                    backwardCamera();
                    return true;
                    
                case irr::KEY_LEFT:  //Camera vers la gauche
                    angleCameraRight();
                    return true;

                case irr::KEY_RIGHT:  //Camera vers la droite
                    angleCameraLeft();
                    return true;

                case irr::KEY_UP:  //Camera avance
                    forwardCamera();
                    return true;
                    
                case irr::KEY_DOWN:  //Camera recule
                    backwardCamera();
                    return true;

                case irr::KEY_KEY_I:  //Camera monte
                    position.Y += 5;
                    target.Y += 5;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);     //Sinon la rotation ce fait mal
                    current_editor->getMainPointer()->camera->setTarget(target);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(true);
                    return true;
                    
                case irr::KEY_KEY_K:  //Camera descend  
                    position.Y -= 5;
                    target.Y -= 5;

                    current_editor->getMainPointer()->camera->setPosition(position);
                    current_editor->getMainPointer()->camera->bindTargetAndRotation(false);     //Sinon la rotation ce fait mal
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
                case irr::gui::EGET_BUTTON_CLICKED:{
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

                    switch(id){             //Creation d'objets
                        case GUI_ID_SQUARE:
                            current_editor->getCurrentZone()->createObjet(cube);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                            
                        case GUI_ID_CIRCLE:
                            current_editor->getCurrentZone()->createObjet(circle);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_SPHERE:
                            current_editor->getCurrentZone()->createObjet(sphere);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                            
                        case GUI_ID_CYLINDER:
                            current_editor->getCurrentZone()->createObjet(cylinder);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                            
                        case GUI_ID_RECTANGLE:
                            current_editor->getCurrentZone()->createObjet(rectangle);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                            
                        case GUI_ID_LINE:
                            current_editor->getCurrentZone()->createObjet(line);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                            
                        case GUI_ID_TRAPEZE:
                            current_editor->getCurrentZone()->createObjet(trapeze);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;

                        case GUI_ID_PYRAMID:
                            current_editor->getCurrentZone()->createObjet(pyramid);
                            current_editor->getCurrentZone()->getObjetPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
                            return true;
                    }}
                    break; 
                  
                case irr::gui::EGET_COMBO_BOX_CHANGED:
                    OnObjectSelected((irr::gui::IGUIComboBox*)event.GUIEvent.Caller);
                    break;
            }
        }else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
            if(event.MouseInput.isLeftPressed() == true){       //Si on clique sur un objet a l'ecran il est selectionne
                current_editor->getCurrentZone()->setSelectedObject(current_editor->getMainPointer()->scene->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(irr::core::position2di(event.MouseInput.X, event.MouseInput.Y), 0, false, 0));
            }
        }
    }
    return false;
}

void CEventReceiver::OnObjectSelected(irr::gui::IGUIComboBox* combo ){  //Appele lors de la maj de la combo box
    current_editor->getCurrentZone()->setSelectedObject(combo->getSelected());
}

void CEventReceiver::angleCameraRight(){
    irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();      
    
    rotation.Y -= 10;
    current_editor->getMainPointer()->camera->setRotation(rotation);
}

void CEventReceiver::angleCameraLeft(){
    irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
    
    rotation.Y += 10;
    current_editor->getMainPointer()->camera->setRotation(rotation);
}

void CEventReceiver::forwardCamera(){
    irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
    irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
    irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
    irr::core::vector3df direction;
    irr::core::vector3df direction_mvnt;

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
}

void CEventReceiver::backwardCamera(){
    irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
    irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
    irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
    irr::core::vector3df direction;
    irr::core::vector3df direction_mvnt;

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
}
 

