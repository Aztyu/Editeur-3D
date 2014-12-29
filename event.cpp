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
        irr::core::vector3df position = zone_actuelle->getCamerapointer()->getPosition();
        irr::core::vector3df target = zone_actuelle->getCamerapointer()->getTarget();
        irr::core::vector3df direction;
        float sqaurex = pow(target.X, 2.0);
        float sqaurez = pow(target.Z, 2.0);
        float coeff = 5/(sqrt(sqaurex + sqaurez));
        direction.X = target.X - position.X;
        direction.Y = target.Y - position.Y;
        direction.Z = target.Z - position.Z;
        
        switch(event.KeyInput.Key){
            case irr::KEY_KEY_1:
                //zone_actuelle->createObjet(cylinder);
                std::cout << "1 presse" << std::endl;
                return true;
                break;
            case irr::KEY_KEY_2:
                std::cout << "2 presse" << std::endl;
                return true;
                break;
            case irr::KEY_KEY_3:
                std::cout << "3 presse" << std::endl;
                return true;
                break;
            case irr::KEY_KEY_4:
                std::cout << "4 presse" << std::endl;
                return true;
                break;
            case irr::KEY_KEY_O:
                std::cout << "O presse" << std::endl;
                direction.rotateYZBy(-10, irr::core::vector3df(0.0, 0.0, 0.0));
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
            case irr::KEY_KEY_L:
                std::cout << "L presse" << std::endl;
                direction.rotateYZBy(10, irr::core::vector3df(0.0, 0.0, 0.0));
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
            case irr::KEY_KEY_A:
                std::cout << "A presse" << std::endl;
                direction.rotateXZBy(10, irr::core::vector3df(0.0, 0.0, 0.0));
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
            case irr::KEY_KEY_D:
                std::cout << "L presse" << std::endl;
                direction.rotateXZBy(-10, irr::core::vector3df(0.0, 0.0, 0.0));
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
            case irr::KEY_KEY_W:
                std::cout << "W presse" << std::endl;
                position.X += direction.X*coeff;
                position.Z += direction.Z*coeff;
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setPosition(position);
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
            case irr::KEY_KEY_S:
                std::cout << "S presse" << std::endl;
                position.X -= direction.X*coeff;
                position.Z -= direction.Z*coeff;
                target.X = direction.X + position.X;
                target.Y = direction.Y + position.Y;
                target.Z = direction.Z + position.Z;
                zone_actuelle->getCamerapointer()->setPosition(position);
                zone_actuelle->getCamerapointer()->setTarget(target);
                return true;
                break;
        }
    }
    return false;
}
 

