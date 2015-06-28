/* 
 * File:   SingleObjet.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:06
 */
#include "SingleObject.h"
#include "GroupObject.h"

using namespace std;

SingleObject::SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, object type): Object(obj, name, parent){
    this->parent = NULL;
    this->type = type;
}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, float total_scale, object type) : Object(obj, name, parent, total_scale) {
    this->parent = NULL;
    this->type = type;
}

SingleObject::SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, irr::core::vector3df position, object type) : Object(obj, name, parent, position){
    this->parent = NULL;
    this->type = type;
}

SingleObject::~SingleObject() {
    if(parent != NULL){
        static_cast<GroupObject*>(parent)->removeMember();
    }
    cout << "Object deleted" << endl;
}

void SingleObject::selectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
}

void SingleObject::groupSelectObject() {
    this->objet->getMaterial(0).EmissiveColor = irr::video::SColor(255, 248, 158, 37);
}

void SingleObject::unselectObject() {
    this->objet->getMaterial(0).EmissiveColor = 0;
}

void SingleObject::exportObject(TiXmlElement* windows) {
    TiXmlElement * window;
    window = new TiXmlElement( "Object" );  
    windows->LinkEndChild( window );
    window->SetAttribute("name", this->getName().c_str());
    window->SetAttribute("type", this->getType());
 
    TiXmlElement * position;
    position = new TiXmlElement( "position" ); 
    window->LinkEndChild( position );
    irr::core::vector3df position_vector = this->getPosition();
    position->SetDoubleAttribute("x", position_vector.X);
    position->SetDoubleAttribute("y", position_vector.Y);
    position->SetDoubleAttribute("z", position_vector.Z);
    
    TiXmlElement * rotation;
    rotation = new TiXmlElement( "rotation" ); 
    window->LinkEndChild( rotation );
    irr::core::vector3df rotation_vector = this->getRotation();
    rotation->SetDoubleAttribute("x", rotation_vector.X);
    rotation->SetDoubleAttribute("y", rotation_vector.Y);
    rotation->SetDoubleAttribute("z", rotation_vector.Z);

    TiXmlElement * scale;
    scale = new TiXmlElement( "scale" ); 
    window->LinkEndChild( scale );
    irr::core::vector3df scale_vector = this->getScale();
    scale->SetDoubleAttribute("x", scale_vector.X);
    scale->SetDoubleAttribute("y", scale_vector.Y);
    scale->SetDoubleAttribute("z", scale_vector.Z);
}


void SingleObject::setParent(Object* new_parent){
    
    if(new_parent == NULL){
        if(this->parent != NULL){
            irr::core::matrix4 transformation = this->getSceneNode()->getAbsoluteTransformation();
            GroupObject* old_parent = static_cast<GroupObject*>(this->parent);
            this->objet->setParent(this->default_parent);
            this->parent = NULL;
            this->setPosition(transformation.getTranslation());        //Garde la position actuelle de l'objet lors du chamgement de parent
            this->setRotation(transformation.getRotationDegrees());     //Garde la rotation actuelle de l'objet lors du changement de parent
            
            this->modifyScaleBy(old_parent->getScale());
        }else{
            this->objet->setParent(this->default_parent);
            this->parent = NULL;
        } 
    }else{
        objet->setParent(new_parent->getSceneNode());
        this->parent = new_parent;
    }
}

bool SingleObject::hasParent() {
    return this->parent != NULL;
}

SingleObject* SingleObject::getPointer(){
    return this;
}

object SingleObject::getType() {
    return this->type;
}

std::string SingleObject::getClassType() {
    return "SingleObject";
}

Object* SingleObject::getParent() {
    if(hasParent()){
        return this->parent;
    }else{
        return NULL;
    }
}

void SingleObject::Remove() {
    this->objet->remove();
    this->objet = NULL;
}



bool SingleObject::isInGroup() {
    return this->parent != NULL;
}



