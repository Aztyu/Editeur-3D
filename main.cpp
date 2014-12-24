#include <irrlicht.h>

int main(void)
{
    irr::IrrlichtDevice *device = irr::createDevice (
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800,600),
        32,false,true,false,0);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager ();

    // recuperation du pointeur GUI et creation d'une camera
    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment();
    
    irr::gui::ICursorControl *curseur = device->getCursorControl();
    //curseur->setVisible(false);
    
    irr::SKeyMap keyMap[5];                    // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_W;        // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;
    
    sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
        0,                                     // pas de noeud parent
        100.0f,                                // vitesse de rotation
        0.05f,                                  // vitesse de deplacement
        -1,                                    // pas de numero d'ID
        keyMap,                                // on change la keymap
        5);   
    irr::scene::ICameraSceneNode *camera = sceneManager->getActiveCamera();


        //set up mesh
    irr::scene::IMesh* mesh = sceneManager->getMesh("ressources/cylinder.obj");
    irr::scene::IMeshSceneNode* cylinder = sceneManager->addMeshSceneNode(mesh);
    mesh = sceneManager->getMesh("ressources/plane.obj");
    irr::scene::IMeshSceneNode* plane = sceneManager->addMeshSceneNode(mesh);
    mesh = sceneManager->getMesh("ressources/pyramide.obj");
    irr::scene::IMeshSceneNode* pyramide = sceneManager->addMeshSceneNode(mesh);
    
    cylinder->setScale(irr::core::vector3df(10.0, 10.0, 5.0));
    cylinder->setPosition(irr::core::vector3df(0.0, 10.0, 100.0));
    //cylinder->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //cylinder->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    //cylinder->setParent()
    pyramide->setScale(irr::core::vector3df(15.0, 20.0, 10.0));
    pyramide->setPosition(irr::core::vector3df(0.0, 30.0, 100.0));
    //pyramide->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //pyramide->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    
    plane->setScale(irr::core::vector3df(100.0, 0.0, 100.0));
    plane->setPosition(irr::core::vector3df(0.0, 0.0, 100.0));
    //plane->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //plane->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

    wchar_t titre[200];
    
    irr::scene::ILightSceneNode* lumiere = sceneManager->addLightSceneNode (0, irr::core::vector3df(70.0f, 70.0f, 20.0f),
                               irr::video::SColorf(1.0f,1.0f,1.0f,0.0f), 2000.0f);
    
    while(device->run ())                        // la boucle de rendu
    {
        driver->beginScene(true, true,
            irr::video::SColor(255,255,255,255));
        irr::s32 fps = driver->getFPS();
        irr::core::vector3df posCam;
        posCam = camera->getPosition();

        swprintf(titre, 200, L"FPS : %d, X : %f Y : %f Z : %f", fps, posCam.X, posCam.Y, posCam.Z);
        device->setWindowCaption(titre);
        sceneManager->drawAll();
        gui->drawAll();
        driver->endScene();
    }

    device->drop ();
    return 0;
}