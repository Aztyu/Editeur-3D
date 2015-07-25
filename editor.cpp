/* 
 * File:   editor.cpp
 * Author: Aztyu
 * 
 * Created on 26 décembre 2014, 11:29
 */

#include "Editor.h"
#include "Pointers.h"
#include <iostream>
#include <fstream>
#include <Shlobj.h>

using namespace rapidxml;
using namespace std;

Editor::Editor(Pointer* struct_pointer) : main_pointer(struct_pointer), current_zone(NULL){
    this->main_pointer->current_editor = this;
    createZone("Main");
}

Editor::~Editor() {
    for(int i=0; i<this->zone_array.size(); i++){
        delete this->zone_array[i];
    }
    this->zone_array.clear();
}

Editor* Editor::getEditor(){
    return this;
}

void Editor::createZone(){
    std::string base = "Zone";
    this->createZone(base.c_str());
}

void Editor::createZone(const char* name){
    std::string type = "ressources/form/";
    type += "group";
    type += ".obj";
    std::string base = name;
    std::string base_name = "";
    char buffer[50];
    int i = 0;
    do{
        if(i==0){
            base_name = base;
        }else{
            sprintf(buffer, "%d", i);
            base_name = base + buffer;
        }
        i++;
    }while(this->isNameTaken(base_name));
    irr::scene::ISceneManager* scene = this->main_pointer->scene;
    irr::scene::ISceneNode* test = scene->addMeshSceneNode(scene->getMesh(type.c_str()));
    this->zone_array.push_back(new Zone(base_name.c_str(), main_pointer, test));
    std::cout << "test2" << std::endl;
    this->setCurrentZone(zone_array.size()-1);
}

void Editor::removeZones() {
    for(int i=0; i<this->zone_array.size(); i++){
        zone_array.at(i)->resetChild();
        delete(zone_array.at(i));
    }
    this->zone_array.clear();
    this->current_zone = NULL;
}

void Editor::removeZone(Zone* zone) {
    if(this->zone_array.size() > 1){
        for(int i=0; i<this->zone_array.size(); i++){
            if(this->zone_array[i]->getPointer() == zone){
                zone_array.at(i)->resetChild();
                zone_array.at(i)->Remove();
                delete(zone_array.at(i));
                this->zone_array.erase(this->zone_array.begin()+i);
                
            }
        }
        this->current_zone = NULL;
    }else{
        //print message
    }
}

int Editor::getNumberOfZones() {
    return this->zone_array.size();
}



void Editor::setCurrentZone(Zone* zone){
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getPointer() == zone){
            if(zone != this->current_zone){
                setCurrentZone(i);
            }
        }
    }
}

void Editor::setCurrentZone(int index) {
    if(index >= 0 && index < this->zone_array.size()){
        if(this->current_zone != this->zone_array.at(index)){
            if(this->current_zone != NULL){
                this->setCurrentZoneVisible(false);
                this->current_zone->saveCamera();
            }
            this->current_zone = this->zone_array.at(index);
            this->setCurrentZoneVisible(true);

            this->main_pointer->gui->updateZone(&this->zone_array);
            finishZoneSwitch();
        }
    }
}

Zone* Editor::getCurrentZone(){
    return this->current_zone;
}

void Editor::setMainPointer(Pointer* struct_pointer){
    main_pointer = struct_pointer;
}

void Editor::setCurrentZoneVisible(bool isVisible) {
    this->getCurrentZone()->getMeshPointer()->setVisible(isVisible);
    for(int i=0; i<this->getCurrentZone()->getGroupObjectVector()->size(); i++){
        this->getCurrentZone()->getGroupObjectVector()->at(i)->getSceneNode()->setVisible(isVisible);
    }
}

void Editor::finishZoneSwitch() {
    Zone* zone = this->current_zone;
    this->main_pointer->gui->updateGroupObject(zone->getGroupObjectVector());
    this->main_pointer->gui->updateSingleObject(zone->getSingleObjectVector());
    Object* objet = zone->getSelectedSingleObject();
    if(zone->getSelectedSingleObject() != NULL){
        zone->setSelectedSingleObject(zone->getSelectedSingleObject()->getSceneNode());
    }
    objet = zone->getSelectedGroupObject();
    if(zone->getSelectedGroupObject() != NULL){
        zone->setSelectedGroupObject(zone->getSelectedGroupObject()->getSceneNode());
    }
    
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getPointer() == zone){
            this->main_pointer->gui->setZoneSelected(i);
        }
    }
    
    this->main_pointer->gui->updateWindow(this->current_zone->getSelectedObject());
    this->current_zone->loadCamera();
}


Pointer* Editor::getMainPointer(){
    return main_pointer;
}

bool Editor::isNameTaken(std::string name){
    for(int i=0; i<this->zone_array.size(); i++){
        if(this->zone_array.at(i)->getName() == name){
            return true;
        }
    }
    return false;
}

bool Editor::importData() {
    irr::core::stringw MessageText;
    irr::core::stringw Caption = L"Message - Chargement";
    cout << "Start" << endl;
    xml_document<> doc;
    xml_node<> * root_node;
    string path =  "";//this->OpenFileName("Charger une sauvegarde");
    if(path != ""){
        ifstream theFile(path.c_str());
        if(theFile){
            try{
                removeZones();
                vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
                buffer.push_back('\0');
                doc.parse<0>(&buffer[0]);
                root_node = doc.first_node("Editor");
                for (xml_node<> * zone_node = root_node->first_node("Zone"); zone_node; zone_node = zone_node->next_sibling())
                {
                    if(!strcmp(zone_node->name(),"Zone")){
                        this->importZone(zone_node);
                    }
                }
                MessageText = L"Le chargement a bien été effectué";
                this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                    Caption.c_str(), MessageText.c_str());
            }catch(exception e){
                MessageText = L"Il y a eu un problème lors du chargement, fichier invalide";
                this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                    Caption.c_str(), MessageText.c_str());
            }
        }else{
            MessageText = L"Un problème a été rencontré lors de l'ouverture du fichier";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), MessageText.c_str());
        }
        return true;
    }else{
        /*MessageText = L"Aucun fichier choisi.\nLe chargement n'a pas pu être effectué";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), MessageText.c_str());*/
        irr::core::stringw MessageText = L"Cette fonctionnalité n'est pas encore présente sur cette version du logiciel";
        irr::core::stringw Caption = L"Message - En chantier";
        this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), 
                MessageText.c_str());
        return false;
    }
}

void Editor::importZone(xml_node<> *zone_node) {
    this->createZone(zone_node->first_attribute("name")->value());
    for(xml_node<> * object_node = zone_node->first_node(0); object_node; object_node = object_node->next_sibling()){
        char * test = object_node->name();
        if(!strcmp(object_node->name(),"Object")){
            this->current_zone->importObject(object_node);
        }else if(!strcmp(object_node->name(),"Group")){
            this->current_zone->importGroup(object_node);
        }
    }
}

void Editor::exportData(){
    irr::core::stringw MessageText;
    irr::core::stringw Caption = L"Message - Sauvegarde";
    
    string path = ""; //this->GetFileName("Sauvegarder votre travail");
    if(path != ""){ 
        try{
            TiXmlDocument doc;  
            TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
            doc.LinkEndChild( decl );  

            TiXmlElement * root = new TiXmlElement( "Editor" );  
            doc.LinkEndChild( root );  

            for(int i = 0; i < this->zone_array.size(); i++){
                zone_array.at(i)->exportZone(root);
            }

            doc.SaveFile(path.c_str());
            MessageText = L"La sauvegarde a bien été effectué";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), MessageText.c_str());
        }catch(exception e){
            MessageText = L"Il y a eu un problème lors de la sauvegarde du fichier.\nRéessayer avec un autre nom de fichier";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), MessageText.c_str());
        }
    }else{
        /*MessageText = L"Aucun fichier choisi.\nLa sauvegarde n'a pas été effectuée";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                Caption.c_str(), MessageText.c_str());*/
        irr::core::stringw MessageText = L"Cette fonctionnalité n'est pas encore présente sur cette version du logiciel";
            irr::core::stringw Caption = L"Message - En chantier";
            this->main_pointer->gui->getGUIEnvironment()->addMessageBox(
                    Caption.c_str(), 
                    MessageText.c_str());
    }
} 