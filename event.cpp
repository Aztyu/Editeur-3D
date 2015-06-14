#include "Event.h"
#include "iostream"
 
CEventReceiver::CEventReceiver(Editor* editor){
    this->current_editor = editor;
    this->custom_gui = this->current_editor->getMainPointer()->gui;
}
 
bool CEventReceiver::OnEvent(const irr::SEvent &event){
    if(current_editor != NULL){            //On verifie que le pointeur est ok
        if(event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == true){
            irr::core::vector3df position = current_editor->getMainPointer()->camera->getPosition();
            irr::core::vector3df rotation = current_editor->getMainPointer()->camera->getRotation();
            irr::core::vector3df target = current_editor->getMainPointer()->camera->getTarget();
            int focus_id = -1;
            
            if(current_editor->getMainPointer()->gui->getGUIEnvironment()->getFocus() != NULL){
                focus_id = current_editor->getMainPointer()->gui->getGUIEnvironment()->getFocus()->getID();
            }
            bool hasfocus = false;
            bool exist = (current_editor->getMainPointer()->gui->getGUIEnvironment()->getRootGUIElement()->getElementFromId(GUI_ID_OBJECT_WINDOW_OBJECT_NAME, true) != NULL);
            
            if(focus_id >= GUI_ID_OBJECT_WINDOW && focus_id <= GUI_ID_OBJECT_WINDOW_GROUP_COMBO_BOX){
                hasfocus = true;
            }
            

            if(!exist || !hasfocus){
                switch(event.KeyInput.Key){                        
                    case irr::KEY_ESCAPE:  //Ferme le programme
                        current_editor->getMainPointer()->device->closeDevice();
                        return true;

                    case irr::KEY_DELETE:  //Supprime l'objet selectionne
                        current_editor->getCurrentZone()->removeObject(current_editor->getCurrentZone()->getSelectedObject());
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
        }else if (event.EventType == irr::EET_GUI_EVENT){
            irr::s32 id = event.GUIEvent.Caller->getID();
            switch(event.GUIEvent.EventType)
            {
                case irr::gui::EGET_MENU_ITEM_SELECTED:                     // a menu item was clicked
                    OnMenuItemSelected((irr::gui::IGUIContextMenu*)event.GUIEvent.Caller );
                    break;
                case irr::gui::EGET_BUTTON_CLICKED:{
                    if(id <= GUI_ID_OBJECT_WINDOW_GROUP_COMBO_BOX && id >= GUI_ID_OBJECT_WINDOW_OBJECT_NAME){
                        this->OnToolBoxItemSelected(id, event.GUIEvent.Caller);
                    }else{
                        this->OnObjectCreation(id);
                    }}
                    break; 
                  
                case irr::gui::EGET_COMBO_BOX_CHANGED:
                    OnObjectSelected((irr::gui::IGUIComboBox*)event.GUIEvent.Caller);
                    return true;
                    break;
                case irr::gui::EGET_EDITBOX_ENTER:
                    OnValueChanged((irr::gui::IGUIEditBox*)event.GUIEvent.Caller);
                    return true;
                    break;
            }
        }else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
            if(event.MouseInput.isLeftPressed() == true){       //Si on clique sur un objet a l'ecran il est selectionne
                irr::core::vector2di position = irr::core::vector2di(event.MouseInput.X, event.MouseInput.Y);
                if(!this->current_editor->getMainPointer()->gui->isInWindow(position)){ //Si le clic est en dehors de la fenetre outil
                    if(current_editor->getCurrentZone()->setSelectedSingleObject(current_editor->getMainPointer()->scene->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(irr::core::position2di(event.MouseInput.X, event.MouseInput.Y), -1, false, 0))){
                        current_editor->getMainPointer()->gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());
                    }
                }
            }
        }
    }
    return false;
}

void CEventReceiver::OnObjectSelected(irr::gui::IGUIComboBox* combo ){  //Appele lors de la maj de la combo box
    switch(combo->getID()){
        case GUI_ID_SINGLE_OBJECT_COMBO_BOX:
            current_editor->getCurrentZone()->setSelectedSingleObject(combo->getSelected());
            current_editor->getMainPointer()->gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());
            break;
        case GUI_ID_GROUP_OBJECT_COMBO_BOX:
            current_editor->getCurrentZone()->setSelectedGroupObject(combo->getSelected());
            current_editor->getMainPointer()->gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());
            break;
        case GUI_ID_ZONE_COMBO_BOX:
            current_editor->setCurrentZone(combo->getSelected());
            break;
        default:
            break;
    }
}

void CEventReceiver::OnMenuItemSelected(irr::gui::IGUIContextMenu* menu) {
    irr::s32 id = menu->getItemCommandId(menu->getSelectedItem());

    switch(id)
    {
        case GUI_ID_QUIT:
            current_editor->getMainPointer()->device->closeDevice();
            break;
        case GUI_ID_TOOLBOX:
            this->current_editor->getMainPointer()->gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());             
            break;
        case GUI_ID_SKYBOX:
            menu->setItemChecked(menu->getSelectedItem(), !menu->isItemChecked(menu->getSelectedItem()));
            this->current_editor->getMainPointer()->gui->getSkybox()->setVisible(!this->current_editor->getMainPointer()->gui->getSkybox()->isVisible());
            break;
        case GUI_ID_NEW_ZONE:
            this->current_editor->createZone();
            break;
        case GUI_ID_NEW_GROUP:
            this->current_editor->getCurrentZone()->createGroupObject();
            break;
        case GUI_ID_LOAD:
            this->current_editor->removeZones();
            this->current_editor->importData();
            this->custom_gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());
            break;
        case GUI_ID_SAVE:
            this->current_editor->exportData();
            break;
    }
}

void CEventReceiver::OnToolBoxItemSelected(irr::s32 id, irr::gui::IGUIElement* item) {
    Object* target = this->current_editor->getMainPointer()->gui->getTargetObject();
    if(target != NULL){
        irr::core::vector3df modification = irr::core::vector3df();
        if(id <= GUI_ID_OBJECT_WINDOW_POSITION_Z_DOWN && id >= GUI_ID_OBJECT_WINDOW_POSITION_X_UP){
            switch(id){
                case GUI_ID_OBJECT_WINDOW_POSITION_X_UP:
                    modification.X = 1;
                    break;
                case GUI_ID_OBJECT_WINDOW_POSITION_X_DOWN:
                    modification.X = -1;
                    break;
                case GUI_ID_OBJECT_WINDOW_POSITION_Y_UP:
                    modification.Y = 1;
                    break;
                case GUI_ID_OBJECT_WINDOW_POSITION_Y_DOWN:
                    modification.Y = -1;
                    break;
                case GUI_ID_OBJECT_WINDOW_POSITION_Z_UP:
                    modification.Z = 1;
                    break;
                case GUI_ID_OBJECT_WINDOW_POSITION_Z_DOWN:
                    modification.Z = -1;
                    break;
            }
            target->modifyPositionBy(modification);
            this->custom_gui->updateWindow();
        }else if(id <= GUI_ID_OBJECT_WINDOW_ROTATION_Z_DOWN && id >= GUI_ID_OBJECT_WINDOW_ROTATION_X_UP){
            switch(id){
                case GUI_ID_OBJECT_WINDOW_ROTATION_X_UP:
                    modification.X = 15;
                    break;
                case GUI_ID_OBJECT_WINDOW_ROTATION_X_DOWN:
                    modification.X = -15;
                    break;
                case GUI_ID_OBJECT_WINDOW_ROTATION_Y_UP:
                    modification.Y = 15;
                    break;
                case GUI_ID_OBJECT_WINDOW_ROTATION_Y_DOWN:
                    modification.Y = -15;
                    break;
                case GUI_ID_OBJECT_WINDOW_ROTATION_Z_UP:
                    modification.Z = 15;
                    break;
                case GUI_ID_OBJECT_WINDOW_ROTATION_Z_DOWN:
                    modification.Z = -15;
                    break;
            }
            target->modifyRotationBy(modification);
            this->custom_gui->updateWindow();
        }else if(id <= GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_DOWN && id >= GUI_ID_OBJECT_WINDOW_SCALE_X_UP){
            switch(id){
                case GUI_ID_OBJECT_WINDOW_SCALE_X_UP:
                    modification.X = 1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_X_DOWN:
                    modification.X = -1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_Y_UP:
                    modification.Y = 1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_Y_DOWN:
                    modification.Y = -1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_Z_UP:
                    modification.Z = 1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_Z_DOWN:
                    modification.Z = -1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_UP:
                    modification.X = 1.1;
                    modification.Y = 1.1;
                    modification.Z = 1.1;
                    break;
                case GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_DOWN:
                    modification.X = -1.1;
                    modification.Y = -1.1;
                    modification.Z = -1.1;
                    break;
            }
            target->modifyScaleBy(modification);
            this->custom_gui->updateWindow();
        }else{
            switch(id){
                case GUI_ID_OBJECT_WINDOW_REMOVE_FROM_GROUP:{
                    SingleObject* single = static_cast<SingleObject*>(target);
                    if(single->hasParent()){
                        GroupObject* group_object = static_cast<GroupObject*>(single->getParent());
                        group_object->removeMember(single);
                        this->custom_gui->updateWindow();
                    }
                    break;
                }
                case GUI_ID_OBJECT_WINDOW_ADD_TO_GROUP:
                    irr::gui::IGUIElement* window = item->getParent();
                    irr::gui::IGUIElement* combo = window->getElementFromId(GUI_ID_OBJECT_WINDOW_GROUP_COMBO_BOX, true);
                    irr::gui::IGUIComboBox* group_box = static_cast<irr::gui::IGUIComboBox*>(combo);
                    int index = group_box->getSelected();
                    this->current_editor->getCurrentZone()->addToGroup(index);
                    this->custom_gui->updateWindow();
                    break;
            }
        }
    }
}

void CEventReceiver::OnValueChanged(irr::gui::IGUIEditBox* editbox) {
    int id = editbox->getID();
    irr::core::vector3df modification = irr::core::vector3df();
    Object* target = this->current_editor->getMainPointer()->gui->getTargetObject();
    
    irr::gui::IGUIElement* root = this->custom_gui->getGUIEnvironment()->getRootGUIElement();
    irr::core::stringc s = root->getElementFromId(id, true)->getText();
    
    
    if(id <= GUI_ID_OBJECT_WINDOW_POSITION_Z_VALUE && id >= GUI_ID_OBJECT_WINDOW_POSITION_X_VALUE){
        irr::f32 value = (irr::f32)atof(s.c_str());
        modification = target->getPosition();
        switch(id){
            case GUI_ID_OBJECT_WINDOW_POSITION_X_VALUE:
                modification.X = value;
                break;
            case GUI_ID_OBJECT_WINDOW_POSITION_Y_VALUE:
                modification.Y = value;
                break;
            case GUI_ID_OBJECT_WINDOW_POSITION_Z_VALUE:
                modification.Z = value;
                break;
        }
        target->setPosition(modification);
        this->custom_gui->updateWindow();
    }else if(id <= GUI_ID_OBJECT_WINDOW_ROTATION_Z_VALUE && id >= GUI_ID_OBJECT_WINDOW_ROTATION_X_VALUE){
        irr::f32 value = (irr::f32)atof(s.c_str());
        modification = target->getRotation();
        switch(id){
            case GUI_ID_OBJECT_WINDOW_ROTATION_X_VALUE:
                modification.X = value;
                break;
            case GUI_ID_OBJECT_WINDOW_ROTATION_Y_VALUE:
                modification.Y = value;
                break;
            case GUI_ID_OBJECT_WINDOW_ROTATION_Z_VALUE:
                modification.Z = value;
                break;
        }
        target->setRotation(modification);
        this->custom_gui->updateWindow();
    }else if(id <= GUI_ID_OBJECT_WINDOW_SCALE_Z_VALUE && id >= GUI_ID_OBJECT_WINDOW_SCALE_X_VALUE){
        irr::f32 value = (irr::f32)atof(s.c_str());
        modification = target->getScale();
        switch(id){
            case GUI_ID_OBJECT_WINDOW_SCALE_X_VALUE:
                modification.X = value;
                break;
            case GUI_ID_OBJECT_WINDOW_SCALE_Y_VALUE:
                modification.Y = value;
                break;
            case GUI_ID_OBJECT_WINDOW_SCALE_Z_VALUE:
                modification.Z = value;
                break;
        }
        target->setScale(modification);
        this->custom_gui->updateWindow();
    }else if(id == GUI_ID_OBJECT_WINDOW_OBJECT_NAME){
        std::string value = s.c_str();
        this->current_editor->getCurrentZone()->getSelectedObject()->setName(value);
        if(target->getClassType() == "SingleObject"){
            this->current_editor->getCurrentZone()->sendSingleObjectUpdate();
        }else{
            this->current_editor->getCurrentZone()->sendGroupObjectUpdate();
        }
    }
    current_editor->getMainPointer()->gui->updateWindow(this->current_editor->getCurrentZone()->getSelectedObject());
}


void CEventReceiver::OnObjectCreation(irr::s32 id) {
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
        case GUI_ID_CUBE:
            current_editor->getCurrentZone()->createSingleObject(cube);
            break;

        case GUI_ID_CIRCLE:
            current_editor->getCurrentZone()->createSingleObject(circle);
            break;

        case GUI_ID_SPHERE:
            current_editor->getCurrentZone()->createSingleObject(sphere);
            break;

        case GUI_ID_CYLINDER:
            current_editor->getCurrentZone()->createSingleObject(cylinder);
            break;

        case GUI_ID_SQUARE:
            current_editor->getCurrentZone()->createSingleObject(rectangle);
            break;

        case GUI_ID_LINE:
            current_editor->getCurrentZone()->createSingleObject(line);
            break;

        case GUI_ID_TRAPEZE:
            current_editor->getCurrentZone()->createSingleObject(trapeze);
            break;

        case GUI_ID_PYRAMID:
            current_editor->getCurrentZone()->createSingleObject(pyramid);
            break;
    }
    current_editor->getCurrentZone()->getSingleObjectPointer(current_editor->getCurrentZone()->getObjectCount()-1)->setPosition(position.X, position.Y, position.Z);
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






 

