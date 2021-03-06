/* 
 * File:   GroupObject.cpp
 * Author: Aztyu
 * 
 * Created on 21 avril 2015, 17:07
 */

#include "GroupObject.h"

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent): Object(obj, name, parent){
    this->objet->setParent(parent);
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, float total_scale) : Object(obj, name, parent, total_scale) {
    this->objet->setParent(parent);
}

GroupObject::GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, const irr::core::vector3df& position) : Object(obj, name, parent, position){
    this->objet->setParent(parent);
}

GroupObject::~GroupObject() {
    /*if(this->objet != NULL){
        this->unselectObject();
    }*/
    //this->objet->remove();        //Suppression de l'objet dans irrlicht
    std::cout << "Object deleted" << std::endl;
}

void GroupObject::selectObject() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->groupSelectObject();
    }
}

void GroupObject::unselectObject() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->unselectObject();
    }
}

void GroupObject::addMember(SingleObject* object) {
    this->member_object.push_back(object);
    object->setParent(this);
}

void GroupObject::removeMember(int index) {
    if(index >= 0 && index < this->member_object.size()){
        if(this->member_object[index] != NULL){
            if(this->member_object[index]->getSceneNode() != NULL){
                this->member_object[index]->setParent(NULL);
            }
            this->member_object.erase(this->member_object.begin()+index);
        }
    }
}

void GroupObject::removeMember(SingleObject* object) {
    for(int i = 0;i<this->member_object.size(); ++i){
        if(object == this->member_object[i]){
            this->removeMember(i);
            return;
        }
    }
}

void GroupObject::removeMember() {
    for(int i = 0;i<this->member_object.size(); ++i){
        if(this->member_object[i]->getSceneNode() == NULL){
            this->removeMember(i);
            return;
        }
    }
}

void GroupObject::exportObject(TiXmlElement* windows) {
    TiXmlElement * window;
    window = new TiXmlElement( "Group" );  
    windows->LinkEndChild( window );
    window->SetAttribute("name", this->getName().c_str());
 
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
    
    for(int i=0; i<this->member_object.size(); i++){
        this->member_object.at(i)->exportObject(window);
    }
}

std::string GroupObject::getClassType() {
    return "GroupObject";
}

void GroupObject::Remove(){
    this->objet->remove(); 
    this->objet = NULL;
}

void GroupObject::updateChild() {
    for(int i =0; i<this->member_object.size(); i++){
        this->member_object[i]->unselectObject();
        this->member_object[i]->setParent(NULL);
    }
}
