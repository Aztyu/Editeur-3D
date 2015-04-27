#include "Zone.h"
#include "Event.h"
//#include "Pointers.h"

using namespace std;

int main(void)
{
    
    irr::SIrrlichtCreationParameters params = irr::SIrrlichtCreationParameters();
    params.AntiAlias = 16;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2d<irr::u32>(1280, 720);
    params.Bits = 32;
    params.Fullscreen = false;
    params.Stencilbuffer = true;
    params.Vsync = true;
    params.EventReceiver = 0;
    params.Doublebuffer = true;
    
    irr::IrrlichtDevice *device = irr::createDeviceEx(params);
    
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    
    irr::scene::ISceneManager *sceneManager = device->getSceneManager();
    
    irr::gui::ICursorControl *curseur = device->getCursorControl();
    
    //irr::scene::ISceneCollisionManager *collision = sceneManager->getSceneCollisionManager();
    
    sceneManager->addCameraSceneNode(       // ajout de la camera
        0,                                       //idparent
        irr::core::vector3df(0.0, 10.0, -30.0),  //position                                    
        irr::core::vector3df(0.0, 0.0, 0.0),     //regard
        -1,                                      //id camera(pas d'id))
        true); 

    
    irr::scene::ICameraSceneNode *camera = sceneManager->getActiveCamera();
    camera->bindTargetAndRotation(true);
    camera->setRotation(irr::core::vector3df(0.0, 0.0, 0.0));
    
    irr::scene::ISceneNode* Skybox = sceneManager->addSkyBoxSceneNode(
        driver->getTexture("ressources/sky_up.jpg"),
        driver->getTexture("ressources/sky_down.jpg"),
        driver->getTexture("ressources/sky_left.jpg"),
        driver->getTexture("ressources/sky_right.jpg"),
        driver->getTexture("ressources/sky_front.jpg"),
        driver->getTexture("ressources/sky_back.jpg"));
    Skybox->setVisible(false);
    
    Pointer main_pointers;

    Editor editeur(&main_pointers);
    
    CEventReceiver receiver(&editeur); //bind de la gestion d'event
    device->setEventReceiver(&receiver);
    
    GraphicalInterface gui = GraphicalInterface(device->getGUIEnvironment(), driver, Skybox);
    
    main_pointers.camera = camera;
    main_pointers.device = device;
    main_pointers.driver = driver;
    main_pointers.gui = &gui;
    main_pointers.scene = sceneManager;
    
    editeur.getCurrentZone()->createSingleObjet(cylinder);
    editeur.getCurrentZone()->createSingleObjet(pyramid);
    editeur.getCurrentZone()->createSingleObjet(pyramid);
    editeur.getCurrentZone()->createSingleObjet(sphere);
    editeur.getCurrentZone()->createGroupObject();
    
    editeur.getCurrentZone()->getSingleObjetPointer(1)->setPosition(0.0, 2.0, 0.0);
    
    //editeur.getCurrentZone()->getSingleObjetPointer(1)->setParent(editeur.getCurrentZone()->getSingleObjetPointer(0));
    editeur.getCurrentZone()->getGroupObjectPointer(0)->addMember(editeur.getCurrentZone()->getSingleObjetPointer(0)->getPointer());
    editeur.getCurrentZone()->getGroupObjectPointer(0)->addMember(editeur.getCurrentZone()->getSingleObjetPointer(1)->getPointer());
    
    editeur.getCurrentZone()->getSingleObjetPointer(2)->setPosition(0.0, 0.0, 10.0);
    editeur.getCurrentZone()->getSingleObjetPointer(2)->setScale(1.0, 1.0, 3.0);
    
    //editeur.getCurrentZone()->getSingleObjetPointer(2)->setParent(editeur.getCurrentZone()->getSingleObjetPointer(0));
    editeur.getCurrentZone()->getGroupObjectPointer(0)->addMember(editeur.getCurrentZone()->getSingleObjetPointer(2)->getPointer());
    
    //editeur.getCurrentZone()->getSingleObjetPointer(0)->setRotation(0.0, 45.0, 180.0);
    //editeur.getCurrentZone()->getSingleObjetPointer(0)->setScale(3.0, 3.0, 3.0);
    editeur.getCurrentZone()->getGroupObjectPointer(0)->setRotation(0.0, 45.0, 180.0);
    editeur.getCurrentZone()->getGroupObjectPointer(0)->setScale(3.0, 3.0, 3.0);
    
    editeur.getCurrentZone()->getSingleObjetPointer(3)->setPosition(0.0, 0.0, 20.0);
    
    irr::scene::ILightSceneNode* lumiere = sceneManager->addLightSceneNode (0,
            irr::core::vector3df(100.0f, 70.0f, 100.0f),    //Position de la lumiere
            irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f),    //Couleur de la lumiere
            5200.0f);                                       //Rayon de la lumiere
    
    while(device->run ())                        // la boucle de rendu
    {
        wchar_t titre[200];
        
        driver->beginScene(true, true, irr::video::SColor(255,114,122,124));
        irr::s32 fps = driver->getFPS();
        
        irr::core::vector3df posCam;
        posCam = camera->getRotation();
        swprintf(titre, 200, L"FPS : %d, X : %f Y : %f Z : %f", fps, posCam.X, posCam.Y, posCam.Z);
        device->setWindowCaption(titre);
        
        sceneManager->drawAll();    //Dessin de la scene
        gui.drawAll();
        driver->endScene();
    }

    device->drop();
    return 0;
}