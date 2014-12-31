#include "Zone.h"
#include "event.h"

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

    // recuperation du pointeur GUI
    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment();
    
    irr::gui::ICursorControl *curseur = device->getCursorControl();
    //curseur->setVisible(false);
    

    
    sceneManager->addCameraSceneNode(       // ajout de la camera FPS
        0,                                       //idparent
        irr::core::vector3df(0.0, 10.0, -30.0),  //position                                    
        irr::core::vector3df(0.0, 0.0, 0.0),     //look at
        -1,                                      //id camera(pas d'id))
        true); 

    
    irr::scene::ICameraSceneNode *camera = sceneManager->getActiveCamera();
    camera->bindTargetAndRotation(true);
    camera->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));

    Zone zone_test("zone de test", sceneManager);
    Editor editeur(&zone_test, camera, sceneManager);
    
    CEventReceiver receiver(&editeur); //bind de la gestion d'event
    device->setEventReceiver(&receiver);
    
    irr::gui::IGUIButton *bouton = gui->addButton(
        irr::core::rect<irr::s32>(10,10,42,42),
        0,
        GUI_ID_SQUARE,
        L"1");
    bouton->setImage(driver->getTexture("ressources/squareicon.png"));
    
    irr::gui::IGUIButton *bouton1 = gui->addButton(
        irr::core::rect<irr::s32>(52,10,84,42),
        0,
        GUI_ID_SPHERE,
        L"2");
    bouton1->setImage(driver->getTexture("ressources/sphereicon.png"));
    
    irr::gui::IGUIButton *bouton2 = gui->addButton(
        irr::core::rect<irr::s32>(94,10,126,42),
        0,
        GUI_ID_PYRAMID,
        L"3");
    bouton2->setImage(driver->getTexture("ressources/pyramidicon.png"));
    
    irr::gui::IGUIComboBox* box_object = gui->addComboBox(irr::core::rect<irr::s32>(136,10,236,42), 0, -1);
    
    editeur.setObjectBox(box_object);
    
    zone_test.createObjet(cylinder);
    zone_test.createObjet(pyramid);
    zone_test.createObjet(pyramid);
    zone_test.createObjet(sphere);
    
    zone_test.getObjetPointer(1)->setPosition(0.0, 2.0, 0.0);
    zone_test.getObjetPointer(1)->setParent(zone_test.getObjetPointer(0));
    
    zone_test.getObjetPointer(2)->setPosition(0.0, 0.0, 10.0);
    zone_test.getObjetPointer(2)->setScale(1.0, 1.0, 3.0);
    zone_test.getObjetPointer(2)->setParent(zone_test.getObjetPointer(0));
    
    zone_test.getObjetPointer(0)->setRotation(0.0, 45.0, 180.0);
    zone_test.getObjetPointer(0)->setScale(3.0, 3.0, 3.0);
    
    zone_test.getObjetPointer(3)->setPosition(0.0, 0.0, 20.0);
    
    wchar_t titre[200];
    
    irr::scene::ILightSceneNode* lumiere = sceneManager->addLightSceneNode (0, irr::core::vector3df(70.0f, 70.0f, 20.0f),
                               irr::video::SColorf(1.0f,1.0f,1.0f,0.0f), 2000.0f);

    while(device->run ())                        // la boucle de rendu
    {
        driver->beginScene(true, true, irr::video::SColor(255,125,0,120));
        irr::s32 fps = driver->getFPS();
        irr::core::vector3df posCam;
        posCam = camera->getRotation();
        swprintf(titre, 200, L"FPS : %d, X : %f Y : %f Z : %f", fps, posCam.X, posCam.Y, posCam.Z);
        device->setWindowCaption(titre);
        sceneManager->drawAll();
        gui->drawAll();
        driver->endScene();
    }

    device->drop ();
    return 0;
}