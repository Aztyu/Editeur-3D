/* 
 * File:   Zone.cpp
 * Author: Aztyu
 * 
 * Created on 22 décembre 2014, 15:50
 */

#include "Zone.h"

using namespace std;

Zone::Zone(irr::scene::ISceneManager* scn) {
    scene = scn;
    tableau.reserve(10);
}

Zone::Zone(char* name, irr::scene::ISceneManager* scn){
    zone_name = name;
    scene = scn;
    tableau.reserve(10);
    cout << "Creation de la zone " << zone_name << endl;
}

Zone::Zone(const Zone& orig) {
}

Zone::~Zone() {
}

void Zone::addObjet(Objet* objet){
    tableau.push_back(objet);
}

void Zone::createObjet(){
    tableau.push_back(new Objet(scene->addMeshSceneNode(scene->getMesh("ressources/pyramide.obj"))));
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

