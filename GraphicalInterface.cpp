 /* 
 * File:   GraphicalInterface.cpp
 * Author: Aztyu
 * 
 * Created on 19 avril 2015, 16:48
 */

#include "GraphicalInterface.h"

GraphicalInterface::GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver, irr::scene::ISceneNode* skybox) {
    
    this->gui = gui;
    this->driver = driver;
    this->skybox = skybox;
    
    irr::gui::IGUISkin* skin = this->gui->getSkin(); 
    irr::gui::IGUIFont* font = this->gui->getFont("ressources/font/editorfont11.xml"); 
    if (font){ 
        skin->setFont(font); 
        std::cout << "Font changed" << std::endl;
    }
    
    // disable alpha

    for (irr::s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        irr::video::SColor col = this->gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(255);
        this->gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
    }

    // create the toolbox window
    this->updateWindow();
    
    this->gui->addImage(driver->getTexture("ressources/icon/navbar.jpg"),
    irr::core::position2d<irr::s32>(0,0),
        true,
        0
    );
    
    this->menu = this->gui->addMenu();
    menu->addItem(L"Fichier", GUI_ID_FILE, true, true);
    menu->addItem(L"Réglages", GUI_ID_SETTINGS, true, true);
    menu->addItem(L"Aide", GUI_ID_HELP, true, true);
    
    irr::gui::IGUIContextMenu* submenu;
    
    submenu = menu->getSubMenu(0);
    submenu->addItem(L"Nouveau", GUI_ID_NEW);
    submenu->addItem(L"Charger", GUI_ID_LOAD);
    submenu->addItem(L"Sauvegarder", GUI_ID_SAVE);
    submenu->addSeparator();
    submenu->addItem(L"Quitter", GUI_ID_QUIT);
    
    submenu = menu->getSubMenu(1);
    submenu->addItem(L"Skybox", GUI_ID_SKYBOX);
    submenu->addItem(L"Boite à outils", GUI_ID_TOOLBOX);

    submenu = menu->getSubMenu(2);
    submenu->addItem(L"Documentation", GUI_ID_DOC);
    submenu->addItem(L"À propos", GUI_ID_ABOUT);
    
    irr::gui::IGUIButton *bouton = this->gui->addButton(
        irr::core::rect<irr::s32>(10,30,42,62),
        0,
        GUI_ID_SQUARE,
        L"1");
    bouton->setImage(driver->getTexture("ressources/icon/squareicon.png"));
    
    irr::gui::IGUIButton *bouton1 = this->gui->addButton(
        irr::core::rect<irr::s32>(52,30,84,62),
        0,
        GUI_ID_SPHERE,
        L"2");
    bouton1->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton2 = this->gui->addButton(
        irr::core::rect<irr::s32>(94,30,126,62),
        0,
        GUI_ID_PYRAMID,
        L"3");
    bouton2->setImage(driver->getTexture("ressources/icon/pyramidicon.png"));
    
    irr::gui::IGUIButton *bouton3 = this->gui->addButton(
        irr::core::rect<irr::s32>(136,30,168,62),
        0,
        GUI_ID_CIRCLE,
        L"4");
    bouton3->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton4 = this->gui->addButton(
        irr::core::rect<irr::s32>(178,30,210,62),
        0,
        GUI_ID_CYLINDER,
        L"5");
    bouton4->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton5 = this->gui->addButton(
        irr::core::rect<irr::s32>(220,30,252,62),
        0,
        GUI_ID_RECTANGLE,
        L"6");
    bouton5->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton6 = this->gui->addButton(
        irr::core::rect<irr::s32>(262,30,294,62),
        0,
        GUI_ID_LINE,
        L"7");
    bouton6->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton7 = this->gui->addButton(
        irr::core::rect<irr::s32>(304,30,336,62),
        0,
        GUI_ID_TRAPEZE,
        L"8");    
    bouton7->setImage(driver->getTexture("ressources/icon/sphereicon.png"));
    
    this->single_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(640,30,790,62), 0, GUI_ID_SINGLE_OBJECT_COMBO_BOX);
    
    this->group_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(840,30,990,62), 0, GUI_ID_GROUP_OBJECT_COMBO_BOX);
}

GraphicalInterface::~GraphicalInterface() {
}

void GraphicalInterface::drawAll(){
    this->gui->drawAll();
}

void GraphicalInterface::updateSingleObject(std::vector<SingleObject*>* tableau){
    this->single_object_box->clear();
    
    for(int i = 0; i < tableau->size(); i++){
        std::string name = tableau->at(i)->getName();
        std::wstring widestr = std::wstring(name.begin(), name.end());
        const wchar_t* widecstr = widestr.c_str();
        this->single_object_box->addItem(widecstr); //Ajout de l'objet a la combobox
    }
}

void GraphicalInterface::setSingleObjectSelected(int index){
    this->single_object_box->setSelected(index);
}

void GraphicalInterface::updateGroupObject(std::vector<GroupObject*>* tableau){
    for(int i = 0; i < tableau->size(); i++){
        std::string name = tableau->at(i)->getName();
        std::wstring widestr = std::wstring(name.begin(), name.end());
        const wchar_t* widecstr = widestr.c_str();
        this->group_object_box->addItem(widecstr); //Ajout de l'objet a la combobox
    }
}
    
void GraphicalInterface::setGroupObjectSelected(int index){
    this->group_object_box->setSelected(index);
}

irr::gui::IGUIEnvironment* GraphicalInterface::getGUIEnvironment() {
    return this->gui;
}

void GraphicalInterface::updateWindow(Object* object) {
    this->current_object = object;
    
    irr::gui::IGUIElement* root = this->gui->getRootGUIElement();
    irr::gui::IGUIElement* e = root->getElementFromId(GUI_ID_OBJECT_WINDOW, true);
    
    this->window = NULL;
    
    if (e != NULL){
        irr::core::rect<irr::s32> test = e->getAbsolutePosition();
        e->remove();
        if(test.UpperLeftCorner.X != 1080 || test.UpperLeftCorner.Y != 85){
            this->window = this->gui->addWindow(irr::core::rect<irr::s32>(test.UpperLeftCorner.X, test.UpperLeftCorner.Y, test.LowerRightCorner.X, test.LowerRightCorner.Y),
                false, L"Outils", 0, GUI_ID_OBJECT_WINDOW);
        }else{
            this->window = this->gui->addWindow(irr::core::rect<irr::s32>(1080,85,1280,700),
                false, L"Outils", 0, GUI_ID_OBJECT_WINDOW);
        }
    }else{
        this->window = this->gui->addWindow(irr::core::rect<irr::s32>(1080,85,1280,700),
            false, L"Outils", 0, GUI_ID_OBJECT_WINDOW);
    }
    
    if(this->window != NULL){
        if(object != NULL){
            std::string name = object->getName();
            std::wstring widestr = std::wstring(name.begin(), name.end());
            
            const wchar_t* widecstr = widestr.c_str();
            this->gui->addStaticText(L"Nom : ", irr::core::rect<irr::s32>(10,20,55,50),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(60,25,195,45),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_OBJECT_NAME);
            
            this->gui->addStaticText(L"Position", irr::core::rect<irr::s32>(10,50,195,75),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                    
            this->gui->addButton(irr::core::rect<irr::s32>(20,75,50,105),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_X_DOWN,
                L"-");
            
            this->gui->addStaticText(L"X", irr::core::rect<irr::s32>(55,78,70,105),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            irr::core::vector3df vector = object->getPosition();
            
            widecstr = irr::core::stringw(vector.X).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(70,75,150,105),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_POSITION_X_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(150,75,180,105),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_X_UP,
                L"+");
        
        }else{
            this->gui->addStaticText(L"Test",
                irr::core::rect<irr::s32>(10,20,85,50),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
        }
    }       
}

irr::scene::ISceneNode* GraphicalInterface::getSkybox() {
    return this->skybox;
}

Object* GraphicalInterface::getTargetObject() {
    return this->current_object;
}

bool GraphicalInterface::isInWindow(irr::core::vector2di position) {
    if(this->window != NULL){
        return this->window->getAbsoluteClippingRect().isPointInside(position);
    }else{
        return false;
    }
}




