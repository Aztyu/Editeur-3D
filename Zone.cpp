/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"
#include "fstream"
#include "Editor.h"

using namespace std;

Zone::Zone(char* name, Pointer* pointer, irr::scene::ISceneNode* obj): zone_name(name){
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
    current_pointer->gui->updateSingleObject(&this->single_object_array);     //Et de la combobox
}

void Zone::removeGroupObject(int index) {
    if(selected_group == this->group_object_array[index]){
        selected_group = NULL;
    }
    delete this->group_object_array[index];      //On l'enleve du programme
    this->group_object_array.erase(this->group_object_array.begin()+index);       //et du vector
    current_pointer->gui->updateGroupObject(&this->group_object_array);     //Et de la combobox
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
                sprintf (buffer, "%d", type_number[5]);
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
    this->single_object_array.push_back(new SingleObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str()), this->zone_mesh), name.c_str(), this->zone_mesh));        //Chargement et creation de l'objet
    current_pointer->gui->updateSingleObject(&this->single_object_array); //Ajout de l'objet a la combobox
    current_pointer->gui->setSingleObjectSelected(this->single_object_array.size()-1);   //Le derniere objet cree est par default selectionne
    if(selected_object == NULL){
        setSelectedSingleObject(this->single_object_array.size());
    }
}

void Zone::createGroupObject(){
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
    this->group_object_array.push_back(new GroupObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str(), this->current_pointer->current_editor->getCurrentZone()->getMeshPointer()));        //Chargement et creation de l'objet
    current_pointer->gui->updateGroupObject(&this->group_object_array); //Ajout de l'objet a la combobox
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
        return 0;
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


void Zone::exportZone(){        //Besoin de travail et deplacement possible dans editor
    ofstream output("C:\\Users\\Aztyu\\Desktop\\testirrlicht.txt", ofstream::out | ofstream::app);
        if(output.is_open()){
            for(int i=0; i<this->single_object_array.size() ;++i){
                output << this->single_object_array[i] << endl;
            }
            output.close();
        }else{
            cout << "error";
        }
}

