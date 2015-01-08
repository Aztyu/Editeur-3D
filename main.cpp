#include "Zone.h"
#include "event.h"
#include "Pointers.h"

using namespace std;

int main(void)
{
    irr::IrrlichtDevice *device = irr::createDevice (
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800,600),
        32,
        false,
        true,
        false,
        0);
    
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager();

    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment();
    
    irr::gui::ICursorControl *curseur = device->getCursorControl();
    //curseur->setVisible(false);
    
    sceneManager->addCameraSceneNode(       // ajout de la camera
        0,                                       //idparent
        irr::core::vector3df(0.0, 10.0, -30.0),  //position                                    
        irr::core::vector3df(0.0, 0.0, 0.0),     //regard
        -1,                                      //id camera(pas d'id))
        true); 

    
    irr::scene::ICameraSceneNode *camera = sceneManager->getActiveCamera();
    camera->bindTargetAndRotation(true);
    camera->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
    
    Pointer main_pointers;

    Zone zone_test("zone de test", &main_pointers);
    Editor editeur(&zone_test, &main_pointers);
    
    CEventReceiver receiver(&editeur); //bind de la gestion d'event
    device->setEventReceiver(&receiver);
    
    irr::gui::IGUIImage *navbar = gui->addImage(driver->getTexture("ressources/navbar.jpg"),
        irr::core::position2d<irr::s32>(0,0),
        true,
        0
        );
    
    irr::gui::IGUIContextMenu* menu = gui->addMenu();
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
    
    irr::gui::IGUIButton *bouton = gui->addButton(
        irr::core::rect<irr::s32>(10,30,42,62),
        0,
        GUI_ID_SQUARE,
        L"1");
    bouton->setImage(driver->getTexture("ressources/squareicon.png"));
    
    irr::gui::IGUIButton *bouton1 = gui->addButton(
        irr::core::rect<irr::s32>(52,30,84,62),
        0,
        GUI_ID_SPHERE,
        L"2");
    bouton1->setImage(driver->getTexture("ressources/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton2 = gui->addButton(
        irr::core::rect<irr::s32>(94,30,126,62),
        0,
        GUI_ID_PYRAMID,
        L"3");
    bouton2->setImage(driver->getTexture("ressources/pyramidicon.png"));
    
    irr::gui::IGUIButton *bouton3 = gui->addButton(
        irr::core::rect<irr::s32>(136,30,168,62),
        0,
        GUI_ID_CIRCLE,
        L"4");
    bouton3->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton4 = gui->addButton(
        irr::core::rect<irr::s32>(178,30,210,62),
        0,
        GUI_ID_CYLINDER,
        L"5");
    bouton4->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton5 = gui->addButton(
        irr::core::rect<irr::s32>(220,30,252,62),
        0,
        GUI_ID_RECTANGLE,
        L"6");
    bouton5->setImage(driver->getTexture("ressources/sphereicon.png"));
    
        irr::gui::IGUIButton *bouton6 = gui->addButton(
        irr::core::rect<irr::s32>(262,30,294,62),
        0,
        GUI_ID_LINE,
        L"7");
    bouton6->setImage(driver->getTexture("ressources/sphereicon.png"));
    
            irr::gui::IGUIButton *bouton7 = gui->addButton(
        irr::core::rect<irr::s32>(304,30,336,62),
        0,
        GUI_ID_TRAPEZE,
        L"8");
    bouton7->setImage(driver->getTexture("ressources/sphereicon.png"));
    
    irr::gui::IGUIComboBox* box_object = gui->addComboBox(irr::core::rect<irr::s32>(640,30,790,62), 0, GUI_ID_OBJECT);
    
    main_pointers.box_object = box_object;
    main_pointers.camera = camera;
    main_pointers.device = device;
    main_pointers.driver = driver;
    main_pointers.gui = gui;
    main_pointers.scene = sceneManager;
    
    zone_test.createObjet(cylinder);
    zone_test.createObjet(pyramid);
    zone_test.createObjet(pyramid);
    zone_test.createObjet(sphere);
    
    //zone_test.getObjetPointer(1)->getSceneNode()->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
    zone_test.getObjetPointer(1)->setPosition(0.0, 2.0, 0.0);
    zone_test.getObjetPointer(1)->setParent(zone_test.getObjetPointer(0));
    
    zone_test.getObjetPointer(2)->setPosition(0.0, 0.0, 10.0);
    zone_test.getObjetPointer(2)->setScale(1.0, 1.0, 3.0);
    zone_test.getObjetPointer(2)->setParent(zone_test.getObjetPointer(0));
    
    zone_test.getObjetPointer(0)->setRotation(0.0, 45.0, 180.0);
    zone_test.getObjetPointer(0)->setScale(3.0, 3.0, 3.0);
    
    zone_test.getObjetPointer(3)->setPosition(0.0, 0.0, 20.0);
    
    wchar_t titre[200];
    
    irr::scene::ILightSceneNode* lumiere = sceneManager->addLightSceneNode (0,
            irr::core::vector3df(100.0f, 70.0f, 100.0f),    //Position de la lumiere
            irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f),    //Couleur de la lumiere
            5200.0f);                                       //Rayon de la lumiere

        irr::scene::ISceneNode *Skybox = sceneManager->addSkyBoxSceneNode(
        driver->getTexture("ressources/sky_up.jpg"),
        driver->getTexture("ressources/sky_down.jpg"),
        driver->getTexture("ressources/sky_left.jpg"),
        driver->getTexture("ressources/sky_right.jpg"),
        driver->getTexture("ressources/sky_front.jpg"),
        driver->getTexture("ressources/sky_back.jpg"));
    
    while(device->run ())                        // la boucle de rendu
    {
        driver->beginScene(true, true, irr::video::SColor(255,114,122,124));
        irr::s32 fps = driver->getFPS();
        
        irr::core::vector3df posCam;
        posCam = camera->getRotation();
        swprintf(titre, 200, L"FPS : %d, X : %f Y : %f Z : %f", fps, posCam.X, posCam.Y, posCam.Z);
        device->setWindowCaption(titre);
        
        sceneManager->drawAll();    //Dessin de la scene
        gui->drawAll();
        driver->endScene();
    }

    device->drop ();
    return 0;
}