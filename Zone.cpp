/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"

using namespace std;

Zone::Zone(char* name, Pointer* pointer){
    zone_name = name;
    tableau.reserve(10);
    
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
    for(int i=0 ; i<tableau.size() ; ++i){
        delete tableau[i];
    }
    tableau.clear();
}

void Zone::addObjet(Objet* objet){
    tableau.push_back(objet);
}

void Zone::removeObjet(int index){ //clear l'objet de tout stockage et de la scene
    delete tableau[index];
    tableau.erase(tableau.begin()+index);
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
    tableau.push_back(new Objet(current_pointer->scene->addMeshSceneNode(current_pointer->scene->getMesh(type.c_str())), name.c_str()));        //Chargement et creation de l'objet
    std::wstring widestr = std::wstring(name.begin(), name.end());
    const wchar_t* widecstr = widestr.c_str();
    current_pointer->box_object->addItem(widecstr); //Ajout de l'objet a la combobox
    
    setSelectedObject(tableau.size()-1);    //Le derniere objet cree est par default selectionne
}

int Zone::getObjectCount(){
    return tableau.size();
}

void Zone::printZone(){
    cout << "La zone s'appelle " << zone_name << endl;
    for(int i=0; i < tableau.size(); i++){
        tableau[i]->printObjet();
    }
}

Objet* Zone::getObjetPointer(int index){
    if(index >= 0 && index < tableau.size()){
        return tableau[index];
    }else{
        return 0;
    }
}

Zone* Zone::getPointer(){
    return this;
}

void Zone::setSelectedObject(int index){
   if(selected_object != 0){    
       selected_object->getSceneNode()->getMaterial(0).EmissiveColor = 0;   //Si un objet est deja selectionne on le deselectionne en "l'eteignant"
   }
   selected_object = tableau[index];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
   selected_object->getSceneNode()->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
}

void Zone::setSelectedObject(irr::scene::ISceneNode* objet){
    for(int i = 0;i<tableau.size(); ++i){
        if(objet == tableau[i]->getSceneNode()){
            if(selected_object != 0){    
                selected_object->getSceneNode()->getMaterial(0).EmissiveColor = 0;   //Si un objet est deja selectionne on le deselectionne en "l'eteignant"
            }
            selected_object = tableau[i];        //Mise en place de la selection, changement de l'objet selectionne et ajout de la lumiere
            selected_object->getSceneNode()->getMaterial(0).EmissiveColor = irr::video::SColor(255, 213, 228, 56);
            return;
        }
    }
}

