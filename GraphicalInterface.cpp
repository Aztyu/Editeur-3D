/* 
 * File:   GraphicalInterface.cpp
 * Author: Aztyu
 * 
 * Created on 19 avril 2015, 16:48
 */

#include "GraphicalInterface.h"

GraphicalInterface::GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver) {
    
    this->gui = gui;
    this->driver = driver;
    
    irr::gui::IGUISkin* skin = this->gui->getSkin(); 
    irr::gui::IGUIFont* font = this->gui->getFont("ressources/editorfont11.xml"); 
    if (font){ 
        skin->setFont(font); 
        std::cout << "Font changed" << std::endl;
    }
    
    irr::gui::IGUIImage *navbar = this->gui->addImage(driver->getTexture("ressources/navbar.jpg"),
    irr::core::position2d<irr::s32>(0,0),
        true,
        0
    );
    
    this->menu = this->gui->addMenu();
    menu->addItem(L"Fichier", -1, true, true);
    menu->addItem(L"Réglages", -1, true, true);
    menu->addItem(L"Aide", -1, true, true);
    
    irr::gui::IGUIContextMenu* submenu;
    
    submenu = menu->getSubMenu(0);
    submenu->addItem(L"Nouveau");
    submenu->addItem(L"Charger");
    submenu->addItem(L"Sauvegarder");
    submenu->addSeparator();
    submenu->addItem(L"Quitter");
    
    submenu = menu->getSubMenu(1);
    submenu->addItem(L"Skybox");

    submenu = menu->getSubMenu(2);
    submenu->addItem(L"Documentation");
    submenu->addItem(L"A propos");
    
    irr::gui::IGUIButton *bouton = this->gui->addButton(
        irr::core::rect<irr::s32>(10,30,42,62),
        0,
        GUI_ID_SQUARE,
        L"1");
    bouton->setImage(driver->getTexture("ressources/squareicon.png"));
    
    irr::gui::IGUIButton *bouton1 = this->gui->addButton(
        irr::core::rect<irr::s32>(52,30,84,62),
        0,
        GUI_ID_SPHERE,
        L"2");
    bouton1->setImage(driver->getTexture("ressources/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton2 = this->gui->addButton(
        irr::core::rect<irr::s32>(94,30,126,62),
        0,
        GUI_ID_PYRAMID,
        L"3");
    bouton2->setImage(driver->getTexture("ressources/pyramidicon.png"));
    
    irr::gui::IGUIButton *bouton3 = this->gui->addButton(
        irr::core::rect<irr::s32>(136,30,168,62),
        0,
        GUI_ID_CIRCLE,
        L"4");
    bouton3->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton4 = this->gui->addButton(
        irr::core::rect<irr::s32>(178,30,210,62),
        0,
        GUI_ID_CYLINDER,
        L"5");
    bouton4->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton5 = this->gui->addButton(
        irr::core::rect<irr::s32>(220,30,252,62),
        0,
        GUI_ID_RECTANGLE,
        L"6");
    bouton5->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton6 = this->gui->addButton(
        irr::core::rect<irr::s32>(262,30,294,62),
        0,
        GUI_ID_LINE,
        L"7");
    bouton6->setImage(driver->getTexture("ressources/sphereicon.png"));
    
            irr::gui::IGUIButton *bouton7 = this->gui->addButton(
        irr::core::rect<irr::s32>(304,30,336,62),
        0,
        GUI_ID_TRAPEZE,
        L"8");
    bouton7->setImage(driver->getTexture("ressources/sphereicon.png"));
    
    this->single_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(640,30,790,62), 0, GUI_ID_SINGLE_OBJECT_COMBO_BOX);
    
    this->group_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(840,30,990,62), 0, GUI_ID_GROUP_OBJECT_COMBO_BOX);
}

GraphicalInterface::~GraphicalInterface() {
}

void GraphicalInterface::drawAll(){
    this->gui->drawAll();
}

void GraphicalInterface::updateSingleObject(std::vector<SingleObjet*>* tableau){
    this->single_object_box->clear();
    
    for(int i = 0; i < tableau->size(); i++){
        std::string name = tableau->at(i)->getName();
        std::wstring widestr = std::wstring(name.begin(), name.end());
        const wchar_t* widecstr = widestr.c_str();
        this->single_object_box->addItem(widecstr); //Ajout de l'objet a la combobox
    }
}

void GraphicalInterface::setSingleObjetSelected(int index){
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
    
void GraphicalInterface::setGroupObjetSelected(int index){
    this->group_object_box->setSelected(index);
}