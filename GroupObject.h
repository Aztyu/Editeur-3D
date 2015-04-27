/* 
 * File:   GroupObject.h
 * Author: Aztyu
 *
 * Created on 21 avril 2015, 17:07
 */

#ifndef GROUPOBJECT_H
#define	GROUPOBJECT_H

#include "SingleObjet.h"

class GroupObject : public Object{
public:
    GroupObject(irr::scene::ISceneNode* objet, const char* name);
    GroupObject(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    GroupObject(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    GroupObject(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);
    virtual ~GroupObject();
   
    void selectObject();
    void unselectObject();
    
    void addMember(SingleObjet* object);
    void removeMember(int index);
    void removeMember(SingleObjet* object);

    friend std::ostream& operator <<(std::ostream stream, SingleObjet& obj);
    const char* printObjet();
private:
    std::vector<SingleObjet*> member_object;
};

#endif	/* GROUPOBJECT_H */

