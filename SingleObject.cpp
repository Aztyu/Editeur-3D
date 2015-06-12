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
        static_cast<GroupObject*>(parent)->removeMember(this);
    }
    this->objet->remove();        //Suppression de l'objet dans irrlicht
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


std::ostream& operator <<(std::ostream& stream, SingleObject& obj){    //Completer pour l'export
    stream << obj.printObject();
    return stream;
}

const string SingleObject::printObject(){
    std::string obj_name = "L'objet se trouve en ";
    return obj_name;
}

void SingleObject::exportObject(TiXmlElement* windows) {
    TiXmlElement * window;
    window = new TiXmlElement( "Object" );  
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
}


void SingleObject::setParent(Object* parent){
    if(parent == NULL){
        this->objet->setParent(this->default_parent);
        this->parent = NULL;
    }else{
        objet->setParent(parent->getSceneNode());
        this->parent = parent;
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


bool SingleObject::isInGroup() {
    return this->parent != NULL;
}



