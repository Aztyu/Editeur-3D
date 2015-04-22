/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"
#include "fstream"

using namespace std;

Zone::Zone(char* name, Pointer* pointer){
    zone_name = name;
    this->single_object_array.reserve(10);
    for(int i=0; i < 8; i++){ //Mise a zero du nombre d'objets
        type_number[i] = 0;
    }
    current_pointer = pointer;  //liste de pointeurs globaux
    selected_object = NULL;        //Objet selectionne en ce moment   
    cout << "Creation de la zone " << zone_name << endl;
}

Zone::Zone(const Zone& orig) {
}

Zone::~Zone() {
    for(int i=0 ; i<this->single_object_array.size() ; ++i){
        delete this->single_object_array[i];
    }
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

void Zone::createObjet(object form){
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
        setSelectedObject(this->single_object_array.size());
    }
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

SingleObjet* Zone::getSelectedObjet(){
    return selected_object;
}

Zone* Zone::getPointer(){
    return this;
}

void Zone::setSelectedObject(int index){
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

void Zone::setSelectedObject(irr::scene::ISceneNode* objet){
    for(int i = 0;i<this->single_object_array.size(); ++i){
        if(objet == this->single_object_array[i]->getSceneNode()){
            setSelectedObject(i);
            return;
        }
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

