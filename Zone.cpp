/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */


#include "Zone.h"
#include "Pointers.h"
#include "fstream"
#include "Editor.h"
#include <cstdlib>
#include <basetyps.h>

using namespace std;
using namespace rapidxml;

Zone::Zone(const char* name, Pointer* pointer, irr::scene::ISceneNode* obj): zone_name(name){
    this->zone_mesh = obj;
    this->single_object_array.reserve(10);
    for(int i=0; i < 9; i++){ //Mise a zero du nombre d'objets
        this->type_number[i] = 0;
    }
    this->current_pointer = pointer;  //liste de pointeurs globaux
    this->selected_object = NULL;        //Objet selectionne en ce moment
    this->selected_group = NULL;
    cout << "Creation de la zone " << zone_name << endl;
}

Zone::~Zone() {
    this->group_object_array.clear();
    
    this->single_object_array.clear();
}

void Zone::addObject(SingleObject* objet){
    this->single_object_array.push_back(objet);
}

void Zone::removeSingleObject(int index){ //clear l'objet de tout stockage et de la scene
    if(selected_object == this->single_object_array[index]){
        selected_object = NULL;
    }
    delete this->single_object_array[index];      //On l'enleve du programme
    this->single_object_array.erase(this->single_object_array.begin()+index);       //et du vector
    this->sendSingleObjectUpdate();
}

void Zone::removeGroupObject(int index) {
    if(selected_group == this->group_object_array[index]){
        selected_group = NULL;
    }
    delete this->group_object_array[index];      //On l'enleve du programme
    this->group_object_array.erase(this->group_object_array.begin()+index);       //et du vector
    this->sendGroupObjectUpdate();     //Et de la combobox
}


void Zone::removeObject(Object* objet){
    int index = -1;
    
    for(int i = 0;i<this->single_object_array.size(); ++i){
        if(objet == this->single_object_array[i]){
            index = i;
        }
    }
    
    if(index > -1){     //Si l'objet est present on le supprime 
        removeSingleObject(index);
    }else{
        int index = -1;
    
        for(int i = 0;i<this->group_object_array.size(); ++i){
            if(objet == this->group_object_array[i]){
                index = i;
            }
        }
        
        if(index > -1){     //Si l'objet est present on le supprime 
            removeGroupObject(index);
        }
    }
    
    this->current_pointer->gui->updateWindow(this->getSelectedObject()); //Met à jour la fenetre Outils
}

void Zone::createSingleObject(object form){
    char buffer[50];
    string type = "ressources/form/", name;
    switch((int)form){  //Switch qui va choisir quel fichier charger
        case 0:
            name = "Rectangle";
            if(type_number[0] > 0){
                sprintf (buffer, "%d", type_number[0]);
                name.append(buffer);
            }
            type_number[0]++;
            type += "rectangle";
            break;
        case 1:
            name = "Line";
            if(type_number[1] > 0){
                sprintf (buffer, "%d", type_number[1]);
                name.append(buffer);
            }
            type_number[1]++;
            type += "line";
            break;
        case 2:
            name = "Circle";
            if(type_number[2] > 0){
                sprintf (buffer, "%d", type_number[2]);
                name.append(buffer);
            }
            type_number[2]++;
            type += "circle";
            break;
        case 3:
            name = "Trapeze";

            if(type_number[3] > 0){
                sprintf (buffer, "%d", type_number[3]);
                name.append(buffer);
            }
            type_number[3]++;
            type += "trapeze";
            break;
        case 4:
            name = "Cube";
            if(type_number[4] > 0){
                sprintf (buffer, "%d", type_number[4]);
                name.append(buffer);
            }
            type_number[4]++;
            type += "cube";
            break;
        case 5:
            name = "Pyramide";
            if(type_number[5] > 0){
                sprintf(buffer, "%d", type_number[5]);
                name.append(buffer);
            }
            type_number[5]++;
            type += "pyramide";
            break;
        case 6:
            name = "Sphere";
            if(type_number[6] > 0){
                sprintf (buffer, "%d", type_number[6]);
                name.append(buffer);
            }
            type_number[6]++;
            type += "sphere";
            break;
        case 7:
            name = "Cylinder";
            if(type_number[7] > 0){
                sprintf(buffer, "%d", type_number[7]);
                name.append(buffer);
            }
            type_number[7]++;
            type += "cylinder";
            break;
    }
    type += ".obj";
    this->single_object_array.push_back(new SingleObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str()), this->zone_mesh), name.c_str(), this->zone_mesh, form));        //Chargement et creation de l'objet
    this->sendSingleObjectUpdate();
}

void Zone::createGroupObject(SingleObject* base_object){
    string type = "ressources/form/", name;
    name = "Group";
    if(type_number[8] > 0){
        char buffer[50];
        sprintf (buffer, "%d", type_number[8]);
        name.append(buffer);
    }
    type_number[8]++;
    type += "group";
    type += ".obj";
    if(base_object == NULL){
        this->group_object_array.push_back(new GroupObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str(), this->zone_mesh));        //Chargement et creation de l'objet
    }else{
        this->group_object_array.push_back(new GroupObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str(), this->zone_mesh, base_object->getPosition()));        //Chargement et creation de l'objet
        //this->addToGroup(this->group_object_array.size()-1);
        this->group_object_array.at(this->group_object_array.size()-1)->addMember(base_object);
        base_object->setRotation(irr::core::vector3df(0, 0, 0));        //C'est l'objet qui a permis la creation du group donc ses coordonnees sont 0, 0, 0 de même pour la rotation
        base_object->setPosition(irr::core::vector3df(0, 0, 0));
    }
    this->sendGroupObjectUpdate();
    
    if(selected_object == NULL){    //Si aucun objet n'est selectionne alors on selectionne celui-la
        setSelectedGroupObject(this->group_object_array.size()-1);
        current_pointer->gui->setGroupObjectSelected(this->group_object_array.size()-1);
    }
}

void Zone::addToGroup(int index){
    if(index < this->group_object_array.size()){
        SingleObject* base_object = this->selected_object;
        
        GroupObject* new_group = this->group_object_array.at(index);
        
        irr::core::matrix4 matr = base_object->getSceneNode()->getAbsoluteTransformation();
        
        const irr::core::matrix4 group_inv(new_group->getSceneNode()->getAbsoluteTransformation(), irr::core::matrix4::EM4CONST_INVERSE);

        matr = (group_inv*matr);

        new_group->addMember(base_object);
        
        base_object->getSceneNode()->setPosition(matr.getTranslation());
        base_object->getSceneNode()->setRotation(matr.getRotationDegrees());
        
        base_object->getSceneNode()->updateAbsolutePosition();
        irr::core::vector3df scale_base = new_group->getScale();
        irr::core::vector3df scale_mod = scale_base.invert();
        base_object->modifyScaleBy(scale_mod);
        
    }else{
        createGroupObject(this->selected_object);
    }
}

void Zone::importToGroup(int index) {
    SingleObject* base_object = this->selected_object;
    GroupObject* new_group = this->group_object_array.at(index);
    new_group->addMember(base_object);
}


int Zone::getObjectCount(){
    return this->single_object_array.size();
}

void Zone::printZone(){
    cout << "La zone s'appelle " << zone_name << endl;
    for(int i=0; i < this->single_object_array.size(); i++){
        this->single_object_array[i]->printObject();
    }
}

SingleObject* Zone::getSingleObjectPointer(int index){
    if(index >= 0 && index < this->single_object_array.size()){
        return this->single_object_array[index];
    }else{
        return 0;
    }
}

GroupObject* Zone::getGroupObjectPointer(int index){
    if(index >= 0 && index < this->group_object_array.size()){
        return this->group_object_array[index];
    }else{
        return NULL;
    }
}

Object* Zone::getSelectedObject() {
    if(this->selected_object != NULL){
        return this->selected_object;
    }if(this->selected_group != NULL){
        return this->selected_group;
    }else{
        return NULL;
    }
}

SingleObject* Zone::getSelectedSingleObject(){
    return selected_object;
}

Zone* Zone::getPointer(){
    return this;
}

irr::scene::ISceneNode* Zone::getMeshPointer() {
    return this->zone_mesh;
}

std::string Zone::getName() {
    return this->zone_name;
}

std::vector<GroupObject*>* Zone::getGroupObjectVector() {
    return &this->group_object_array;
}

std::vector<SingleObject*>* Zone::getSingleObjectVector() {
    return &this->single_object_array;
}

void Zone::setSelectedSingleObject(int index){
    this->unselectAll();
    
    if(index >= 0 && index < this->single_object_array.size()){
        this->selected_object = this->single_object_array[index];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
        this->selected_object->getSceneNode()->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
        this->current_pointer->gui->setSingleObjectSelected(index);
    }
}

bool Zone::setSelectedSingleObject(irr::scene::ISceneNode* objet){
    for(int i = 0;i<this->single_object_array.size(); ++i){
        if(objet == this->single_object_array[i]->getSceneNode()){
            setSelectedSingleObject(i);
            return true;
        }
    }
    return false;
}

void Zone::setSelectedGroupObject(int index) {
    this->unselectAll();
    if(index >= 0 && index < this->group_object_array.size()){  
        selected_group = this->group_object_array[index];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
        selected_group->selectObject();
        current_pointer->gui->setGroupObjectSelected(index);
    }else{
        this->selected_object = NULL;
    }
}

bool Zone::setSelectedGroupObject(irr::scene::ISceneNode* objet){
    for(int i = 0;i<this->group_object_array.size(); ++i){
        if(objet == this->group_object_array[i]->getSceneNode()){
            setSelectedGroupObject(i);
            return true;
        }
    }
    return false;
}


GroupObject* Zone::getSelectedGroupObject() {
    return this->selected_group;
}

void Zone::unselectAll() {
    if(this->selected_object != NULL){
        this->selected_object->unselectObject();
        this->selected_object = NULL;
    }
    
    if(this->selected_group != NULL){
        this->selected_group->unselectObject();
        this->selected_group = NULL;
    }
}

void Zone::sendGroupObjectUpdate() {
    current_pointer->gui->updateGroupObject(&this->group_object_array);
    if(this->selected_group != NULL){
        this->setSelectedGroupObject(this->selected_group->getSceneNode());
    }
}

void Zone::sendSingleObjectUpdate() {
    current_pointer->gui->updateSingleObject(&this->single_object_array);
    if(this->selected_object != NULL){
        this->setSelectedSingleObject(this->selected_object->getSceneNode());
    }
}

void Zone::exportZone(TiXmlElement* root){        //Besoin de travail et deplacement possible dans editor
    TiXmlElement * windows = new TiXmlElement( "Zone" );  
    root->LinkEndChild( windows );
    windows->SetAttribute("name", this->getName().c_str());
    for(int i = 0; i< this->group_object_array.size(); i++){
        group_object_array.at(i)->exportObject(windows);
    }
    for(int i = 0; i< this->single_object_array.size(); i++){
        SingleObject* object = single_object_array.at(i);
        if(!object->isInGroup()){
            single_object_array.at(i)->exportObject(windows);
        }
    }
}

void Zone::importObject(xml_node<>* object_node){
    object form = (object)atoi(object_node->first_attribute("type")->value());
    this->createSingleObject(form);
    for (xml_node<> * position_node = object_node->first_node("position"); position_node; position_node = position_node->next_sibling())
    {
        char * test = position_node->name();
        if(!strcmp(test, "position")){
            irr::core::vector3df position;
            position.X = atof(position_node->first_attribute("x")->value());
            position.Y = atof(position_node->first_attribute("y")->value());
            position.Z = atof(position_node->first_attribute("z")->value());
            this->single_object_array.at(this->single_object_array.size()-1)->setPosition(position);
        }

        else if(!strcmp(test, "rotation")){
            irr::core::vector3df rotation;
            rotation.X = atof(position_node->first_attribute("x")->value());
            rotation.Y = atof(position_node->first_attribute("y")->value());
            rotation.Z = atof(position_node->first_attribute("z")->value());
            this->single_object_array.at(this->single_object_array.size()-1)->setRotation(rotation);
        }

        else if(!strcmp(test, "scale")){
            irr::core::vector3df scale;
            scale.X = atof(position_node->first_attribute("x")->value());
            scale.Y = atof(position_node->first_attribute("y")->value());
            scale.Z = atof(position_node->first_attribute("z")->value());
            this->single_object_array.at(this->single_object_array.size()-1)->setScale(scale);
        }
    }
}

void Zone::importGroup(xml_node<>* group_node) {
    this->createGroupObject();
    for (xml_node<> * position_node = group_node->first_node("position"); position_node; position_node = position_node->next_sibling())
    {
        char * test = position_node->name();
        if(!strcmp(test, "position")){
            irr::core::vector3df position;
            position.X = atof(position_node->first_attribute("x")->value());
            position.Y = atof(position_node->first_attribute("y")->value());
            position.Z = atof(position_node->first_attribute("z")->value());
            this->group_object_array.at(this->group_object_array.size()-1)->setPosition(position);
        }else if(!strcmp(test, "rotation")){
            irr::core::vector3df rotation;
            rotation.X = atof(position_node->first_attribute("x")->value());
            rotation.Y = atof(position_node->first_attribute("y")->value());
            rotation.Z = atof(position_node->first_attribute("z")->value());
            this->group_object_array.at(this->group_object_array.size()-1)->setRotation(rotation);
        }else if(!strcmp(test, "scale")){
            irr::core::vector3df scale;
            scale.X = atof(position_node->first_attribute("x")->value());
            scale.Y = atof(position_node->first_attribute("y")->value());
            scale.Z = atof(position_node->first_attribute("z")->value());
            this->group_object_array.at(this->group_object_array.size()-1)->setScale(scale);
        }else if(!strcmp(test, "Object")){
            this->importObject(position_node);
            this->setSelectedSingleObject(this->single_object_array.size()-1);
            this->importToGroup(this->group_object_array.size()-1);
        }
    }
}

