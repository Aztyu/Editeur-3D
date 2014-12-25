#include "event.h"
 
CEventReceiver::CEventReceiver(Zone* zone)
{
    //On pointe le mesh passe en parametre.
    zone_actuelle = zone;
}
 
 
bool CEventReceiver::OnEvent(const irr::SEvent &event)
{
    //On verifie que le pointeur est ok
    if(zone_actuelle != 0 && event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == true){
        switch(event.KeyInput.Key){
            case irr::KEY_KEY_1:
                //zone_actuelle->createObjet(cylinder);
                std::cout << "1 presse" << std::endl;
                break;
            case irr::KEY_KEY_2:
                std::cout << "2 presse" << std::endl;
                break;
            case irr::KEY_KEY_3:
                std::cout << "3 presse" << std::endl;
                break;
            case irr::KEY_KEY_4:
                std::cout << "4 presse" << std::endl;
                break;
        }
    }
    return false;
}
 

