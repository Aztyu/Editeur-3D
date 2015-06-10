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
    this->current_object = NULL;
    
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
    submenu->addItem(L"Nouveau...", GUI_ID_NEW, true, true, false, false);
    submenu->addItem(L"Charger", GUI_ID_LOAD);
    submenu->addItem(L"Sauvegarder", GUI_ID_SAVE);
    submenu->addSeparator();
    submenu->addItem(L"Quitter", GUI_ID_QUIT);
    
    submenu = submenu->getSubMenu(0);
    submenu->addItem(L"Groupe", GUI_ID_NEW_GROUP, true, false, false);
    submenu->addItem(L"Zone", GUI_ID_NEW_ZONE, true, false, false);
    
    submenu = menu->getSubMenu(1);
    submenu->addItem(L"Skybox", GUI_ID_SKYBOX);
    submenu->addItem(L"Boite à outils", GUI_ID_TOOLBOX);

    submenu = menu->getSubMenu(2);
    submenu->addItem(L"Documentation", GUI_ID_DOC);
    submenu->addItem(L"À propos", GUI_ID_ABOUT);
    
    driver->setTextureCreationFlag(irr::video::ETCF_OPTIMIZED_FOR_QUALITY);
    irr::gui::IGUIButton *bouton = this->gui->addButton(
        irr::core::rect<irr::s32>(10,30,42,62),
        0,
        GUI_ID_CUBE,
        L"");
    bouton->setImage(driver->getTexture("ressources/icon/cube_icon.png"));
    
    irr::gui::IGUIButton *bouton1 = this->gui->addButton(
        irr::core::rect<irr::s32>(52,30,84,62),
        0,
        GUI_ID_SPHERE,
        L"");
    bouton1->setImage(driver->getTexture("ressources/icon/sphere_icon.png"));
    
    irr::gui::IGUIButton *bouton2 = this->gui->addButton(
        irr::core::rect<irr::s32>(94,30,126,62),
        0,
        GUI_ID_PYRAMID,
        L"");
    bouton2->setImage(driver->getTexture("ressources/icon/pyramid_icon.png"));
    
    irr::gui::IGUIButton *bouton3 = this->gui->addButton(
        irr::core::rect<irr::s32>(136,30,168,62),
        0,
        GUI_ID_CIRCLE,
        L"");
    bouton3->setImage(driver->getTexture("ressources/icon/circle_icon.png"));
    
    irr::gui::IGUIButton *bouton4 = this->gui->addButton(
        irr::core::rect<irr::s32>(178,30,210,62),
        0,
        GUI_ID_CYLINDER,
        L"");
    bouton4->setImage(driver->getTexture("ressources/icon/cylindre_icon.png"));
    
    irr::gui::IGUIButton *bouton5 = this->gui->addButton(
        irr::core::rect<irr::s32>(220,30,252,62),
        0,
        GUI_ID_SQUARE,
        L"");
    bouton5->setImage(driver->getTexture("ressources/icon/square_icon.png"));
    
    irr::gui::IGUIButton *bouton6 = this->gui->addButton(
        irr::core::rect<irr::s32>(262,30,294,62),
        0,
        GUI_ID_LINE,
        L"");
    
    bouton6->setImage(driver->getTexture("ressources/icon/ligne_icon.png"));
    
    irr::gui::IGUIButton *bouton7 = this->gui->addButton(
        irr::core::rect<irr::s32>(304,30,336,62),
        0,
        GUI_ID_TRAPEZE,
        L"");    
    bouton7->setImage(driver->getTexture("ressources/icon/trapeze_icon.png"));
    
    this->gui->addStaticText(L"Objects",
                irr::core::rect<irr::s32>(540,35,630,62),
                false,
                true);
    
    this->gui->addStaticText(L"Groups",
                irr::core::rect<irr::s32>(790,35,880,62),
                false,
                true);
    
    this->gui->addStaticText(L"Zones",
                irr::core::rect<irr::s32>(1040,35,1130,62),
                false,
                true);
    
    this->single_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(630,30,780,62), 0, GUI_ID_SINGLE_OBJECT_COMBO_BOX);
    
    this->group_object_box = this->gui->addComboBox(irr::core::rect<irr::s32>(880,30,1030,62), 0, GUI_ID_GROUP_OBJECT_COMBO_BOX);
    
    this->zone_box = this->gui->addComboBox(irr::core::rect<irr::s32>(1130,30,1280,62), 0, GUI_ID_ZONE_COMBO_BOX);
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
    this->group_object_box->clear();
    
    for(int i = 0; i < tableau->size(); i++){
        std::string name = tableau->at(i)->getName();
        std::wstring widestr = std::wstring(name.begin(), name.end());
        const wchar_t* widecstr = widestr.c_str();
        this->group_object_box->addItem(widecstr);      //Ajout de l'objet a la combobox
    }
}

void GraphicalInterface::updateZone(std::vector<Zone*>* tableau){
    this->zone_box->clear();
    
    for(int i = 0; i < tableau->size(); i++){
        std::string name = tableau->at(i)->getName();
        std::wstring widestr = std::wstring(name.begin(), name.end());
        const wchar_t* widecstr = widestr.c_str();
        this->zone_box->addItem(widecstr);      //Ajout de l'objet a la combobox
    }
}
    

void GraphicalInterface::setGroupObjectSelected(int index){
    this->group_object_box->setSelected(index);
}

void GraphicalInterface::setZoneSelected(int index) {
    this->zone_box->setSelected(index);
}


irr::gui::IGUIEnvironment* GraphicalInterface::getGUIEnvironment() {
    return this->gui;
}

void GraphicalInterface::updateWindow(Object* object) {
    this->current_object = object;
    this->updateWindow();
}

void GraphicalInterface::updateWindow() {
    Object* object = this->current_object;
    
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
            this->gui->addStaticText(L"Nom : ", irr::core::rect<irr::s32>(15,20,60,50),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(60,25,185,45),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_OBJECT_NAME);
            
            this->gui->addStaticText(L"Position", irr::core::rect<irr::s32>(15,50,200,75),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            //Position
                    
            this->gui->addButton(irr::core::rect<irr::s32>(15,75,45,105),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_X_DOWN,
                L"-");
            
            this->gui->addStaticText(L"X", irr::core::rect<irr::s32>(50,78,65,105),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            irr::core::vector3df vector = object->getPosition();
            
            widecstr = irr::core::stringw(vector.X).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,75,145,105),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_POSITION_X_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,75,185,105),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_X_UP,
                L"+");
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,115,45,145),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_Y_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Y", irr::core::rect<irr::s32>(50,118,65,145),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            widecstr = irr::core::stringw(vector.Y).c_str();
            
            this->gui->addEditBox(widecstr,
                irr::core::rect<irr::s32>(65,115,145,145),
                true,
                static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_POSITION_Y_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,115,185,145),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_Y_UP,
                L"+");
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,155,45,185),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_Z_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Z", irr::core::rect<irr::s32>(50,158,65,185),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            widecstr = irr::core::stringw(vector.Z).c_str();
            
            this->gui->addEditBox(widecstr,
                irr::core::rect<irr::s32>(65,155,145,185),
                true,
                static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_POSITION_Z_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,155,185,185),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_POSITION_Z_UP,
                L"+");
            
            //Rotation
            
            this->gui->addStaticText(L"Rotation", irr::core::rect<irr::s32>(15,200,200,225),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,225,45,255),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_X_DOWN,
                L"-");
            
            this->gui->addStaticText(L"X", irr::core::rect<irr::s32>(50,228,65,255),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            vector = object->getRotation();
            
            widecstr = irr::core::stringw(vector.X).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,225,145,255),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_ROTATION_X_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,225,185,255),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_X_UP,
                L"+");
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,265,45,295),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_Y_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Y", irr::core::rect<irr::s32>(50,268,65,295),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            widecstr = irr::core::stringw(vector.Y).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,265,145,295),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_ROTATION_Y_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,265,185,295),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_Y_UP,
                L"+");

            this->gui->addButton(irr::core::rect<irr::s32>(15,305,45,335),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_Z_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Z", irr::core::rect<irr::s32>(50,308,65,335),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
      
            widecstr = irr::core::stringw(vector.Z).c_str();

            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,305,145,335),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_ROTATION_Z_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,305,185,335),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_ROTATION_Z_UP,
                L"+");
            
            //Echelle
            vector = object->getScale();
            
            this->gui->addStaticText(L"Echelle", irr::core::rect<irr::s32>(15,350,200,375),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,375,45,405),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_X_DOWN,
                L"-");
            
            this->gui->addStaticText(L"X", irr::core::rect<irr::s32>(50,378,65,405),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            widecstr = irr::core::stringw(vector.X).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,375,145,405),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_SCALE_X_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,375,185,405),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_X_UP,
                L"+");
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,415,45,445),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_Y_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Y", irr::core::rect<irr::s32>(50,418,65,445),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
                        
            widecstr = irr::core::stringw(vector.Y).c_str();
            
            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,415,145,445),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_SCALE_Y_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,415,185,445),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_Y_UP,
                L"+");

            this->gui->addButton(irr::core::rect<irr::s32>(15,455,45,485),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_Z_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Z", irr::core::rect<irr::s32>(50,458,65,485),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
      
            widecstr = irr::core::stringw(vector.Z).c_str();

            this->gui->addEditBox(widecstr,
                    irr::core::rect<irr::s32>(65,455,145,485),
                    true,
                    static_cast<irr::gui::IGUIElement*>(this->window), GUI_ID_OBJECT_WINDOW_SCALE_Z_VALUE);
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,455,185,485),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_Z_UP,
                L"+");
            
            this->gui->addButton(irr::core::rect<irr::s32>(15,495,45,525),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_DOWN,
                L"-");
            
            this->gui->addStaticText(L"Total", irr::core::rect<irr::s32>(50,498,145,528),
                false,
                true,
                static_cast<irr::gui::IGUIElement*>(this->window));
            
            this->gui->addButton(irr::core::rect<irr::s32>(155,495,185,525),
                static_cast<irr::gui::IGUIElement*>(this->window),
                GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_UP,
                L"+");

        }else{
            
            this->gui->addStaticText(L"None",
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




