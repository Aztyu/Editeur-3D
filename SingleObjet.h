/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

#include "Object.h"

class SingleObjet : public Object{
public:
    SingleObjet(irr::scene::ISceneNode* objet, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);

    void selectObject();
    void groupSelectObject();
    void unselectObject();

    friend std::ostream& operator <<(std::ostream stream, SingleObjet& obj);
    const char* printObjet();
    void setParent(Object* parent);
    bool hasParent();
    SingleObjet* getPointer();
};

#endif	/* SINGLEOBJECT_H */

