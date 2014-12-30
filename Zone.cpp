/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"

using namespace std;

Zone::Zone(char* name, irr::scene::ISceneManager* scene){
    zone_name = name;
    tableau.reserve(10);
    
    for(int i=0; i < 8; i++){
        type_number[i] = 0;
    }
    current_scene = scene;
    
    cout << "Creation de la zone " << zone_name << endl;
}

Zone::Zone(const Zone& orig) {
}

Zone::~Zone() {
}

void Zone::addObjet(Objet* objet){
    tableau.push_back(objet);
}

void Zone::removeObjet(int index){
    tableau[index]->getSceneNode()->remove();
    delete tableau[index]->getPointer();
    tableau.erase(tableau.begin()+index);
}

void Zone::createObjet(object form){
    char name[50];
    string type = "ressources/";
    switch((int)form){
        case 0:
            if(type_number[0] > 0){
                sprintf (name, "Rectangle%d", type_number[0]);
            }else{
                sprintf (name, "Rectangle");
            }
            type += "rectangle";
            type_number[0]++;
            break;
        case 1:
            if(type_number[1] > 0){
                sprintf (name, "Line%d", type_number[1]);
            }else{
                sprintf (name, "Line");
            }
            type += "line";
            type_number[1]++;
            break;
        case 2:
            if(type_number[2] > 0){
                sprintf (name, "Circle%d", type_number[2]);
            }else{
                sprintf (name, "Circle");
            }
            type += "circle";
            type_number[2]++;
            break;
        case 3:
            if(type_number[3] > 0){
                sprintf (name, "Trapeze%d", type_number[3]);
            }else{
                sprintf (name, "Trapeze");
            }
            type += "trapeze";
            type_number[3]++;
            break;
        case 4:
            if(type_number[4] > 0){
                sprintf (name, "Cube%d", type_number[4]);
            }else{
                sprintf (name, "Cube");
            }
            type += "cube";
            type_number[4]++;
            break;
        case 5:
            if(type_number[5] > 0){
                sprintf (name, "Pyramid%d", type_number[5]);
            }else{
                sprintf (name, "Pyramid");
            }
            type += "pyramide";
            type_number[5]++;
            break;
        case 6:
            if(type_number[6] > 0){
                sprintf (name, "Sphere%d", type_number[6]);
            }else{
                sprintf (name, "Sphere");
            }
            type += "sphere";
            type_number[6]++;
            break;
        case 7:
            if(type_number[7] > 0){
                sprintf (name, "Cylinder%d", type_number[7]);
            }else{
                sprintf (name, "Cylinder");
            }
            type += "cylinder";
            type_number[7]++;
            break;
    }
    type += ".obj";
    tableau.push_back(new Objet(current_scene->addMeshSceneNode(current_scene->getMesh(type.c_str())), name));
    //wchar_t buffer [100];
    //swprintf( buffer, 100, L"%s", name);
    //box_global->addItem(buffer);
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

