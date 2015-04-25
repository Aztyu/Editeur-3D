/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"
#include "fstream"

using namespace std;

Zone::Zone(char* name, Pointer* pointer): zone_name(name){
    //this->zone_name = name;
    this->single_object_array.reserve(10);
    for(int i=0; i < 9; i++){ //Mise a zero du nombre d'objets
        this->type_number[i] = 0;
    }
    this->current_pointer = pointer;  //liste de pointeurs globaux
    this->selected_object = NULL;        //Objet selectionne en ce moment
    this->selected_group = NULL;
    cout << "Creation de la zone " << zone_name << endl;
}

Zone::Zone(const Zone& orig) {
}

Zone::~Zone() {
    /*for(int i=0 ; i<this->group_object_array.size() ; ++i){
        delete this->group_object_array[i];
    }*/
    this->group_object_array.clear();
    
    /*for(int i=0 ; i<this->single_object_array.size() ; ++i){
        delete this->single_object_array[i];
    }*/
    this->single_object_array.clear();
}

void Zone::addObjet(SingleObjet* objet){
    this->single_object_array.push_back(objet);
}

void Zone::removeObjet(int index){ //clear l'objet de tout stockage et de la scene
    if(selected_object == this->single_object_array[index]){
        selected_object = NULL;
    }
    delete this->single_object_array[index];      //On l'enleve du programme
    this->single_object_array.erase(this->single_object_array.begin()+index);       //et du vector
    current_pointer->gui->updateSingleObject(&this->single_object_array);     //Et de la combobox
}

void Zone::removeObjet(SingleObjet* objet){
    int index = -1;
    
    for(int i = 0;i<this->single_object_array.size(); ++i){
        if(objet == this->single_object_array[i]){
            index = i;
        }
    }
    
    if(index > -1){     //Si l'objet est present on le supprime 
        removeObjet(index);
    }
}

void Zone::createSingleObjet(object form){
    char buffer[50];
    string type = "ressources/", name;
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
    this->single_object_array.push_back(new SingleObjet(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str()));        //Chargement et creation de l'objet
    current_pointer->gui->updateSingleObject(&this->single_object_array); //Ajout de l'objet a la combobox
    current_pointer->gui->setSingleObjetSelected(this->single_object_array.size()-1);   //Le derniere objet cree est par default selectionne
    if(selected_object == NULL){
        setSelectedSingleObject(this->single_object_array.size());
    }
}

void Zone::createGroupObject(){
    string type = "ressources/", name;
    name = "Group";
    if(type_number[8] > 0){
        char buffer[50];
        sprintf (buffer, "%d", type_number[8]);
        name.append(buffer);
    }
    type_number[8]++;
    type += "rectangle";
    type += ".obj";
    this->group_object_array.push_back(new GroupObject(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), 0.1, name.c_str()));        //Chargement et creation de l'objet
    current_pointer->gui->updateGroupObject(&this->group_object_array); //Ajout de l'objet a la combobox
}

int Zone::getObjectCount(){
    return this->single_object_array.size();
}

void Zone::printZone(){
    cout << "La zone s'appelle " << zone_name << endl;
    for(int i=0; i < this->single_object_array.size(); i++){
        this->single_object_array[i]->printObjet();
    }
}

SingleObjet* Zone::getSingleObjetPointer(int index){
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


SingleObjet* Zone::getSelectedSingleObject(){
    return selected_object;
}

Zone* Zone::getPointer(){
    return this;
}

void Zone::setSelectedSingleObject(int index){
    if(index >= 0 && index < this->single_object_array.size()){
        if(selected_object != 0){    
            selected_object->getSceneNode()->getMaterial(0).EmissiveColor = 0;   //Si un objet est deja selectionne on le deselectionne en "l'eteignant"
        }
        selected_object = this->single_object_array[index];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
        selected_object->getSceneNode()->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
        current_pointer->gui->setSingleObjetSelected(index);
    }else{
        this->selected_object = 0;
    }
}

void Zone::setSelectedSingleObject(irr::scene::ISceneNode* objet){
    for(int i = 0;i<this->single_object_array.size(); ++i){
        if(objet == this->single_object_array[i]->getSceneNode()){
            setSelectedSingleObject(i);
            return;
        }
    }
}

void Zone::setSelectedGroupObject(int index) {
    if(index >= 0 && index < this->group_object_array.size()){
        this->unselectAll();
        selected_group = this->group_object_array[index];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
        selected_group->selectObject();
        current_pointer->gui->setGroupObjetSelected(index);
    }else{
        this->selected_object = NULL;
    }
}

void Zone::unselectAll() {
    if(this->selected_object != NULL){
        this->selected_object->unselectObject();
    }
    if(this->selected_group != NULL){
        this->selected_group->unselectObject();
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

