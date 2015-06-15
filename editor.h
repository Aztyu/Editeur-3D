/* 
 * File:   editor.h
 * Author: Aztyu
 *
 * Created on 26 décembre 2014, 11:29
 */

#ifndef EDITOR_H
#define	EDITOR_H

#include "GraphicalInterface.h"

//! Classe de base qui contient toutes les zones et la plupart des informations
class Editor {
    public:
        //! Constructeur de base.
        /** \param struct_pointer Pointeur vers la structure Pointers.*/
        Editor(Pointer* struct_pointer);
        
        //! Destructeur de base.
        virtual ~Editor();
        
        //Gestion des zones
        //! Creer une zone ayant un nom donne.
        /** \param base_name Le nom de la zone à créer.*/
        void createZone(const char* base_name);
        
        //! Creer une zone sans nom specifique.*/
        void createZone();
        
        void removeZones();
        
        //! Definit la zone actuelle.
        /** \param zone Pointeur vers la zone à définir comme actuelle.*/
        void setCurrentZone(Zone* zone);
        
        //! Selectionne une Zone selon sa position dans le vector.
        /** \param index Position de l'objet dans le vector zone_array. */
        void setCurrentZone(int index);
        
        //! Definit le Pointers utilisé dans le programme.
        /** \param struct_pointer Pointeur vers le Pointers à utiliser.*/
        void setMainPointer(Pointer* struct_pointer);
        
        //! Change la visibilite de la Zone et les GroupObject.
        /** \param isVisible booleen qui definit la visibilite ou non.*/
        void setCurrentZoneVisible(bool isVisible);
        
        //! Effectue toutes les operations necessaires au changement de Zone.*/
        void finishZoneSwitch();
                
        //Recuperation d'informations
        //! Renvoie le Pointers utilisé.
        /** \return Un pointer vers le Pointers utilisé.*/
        Pointer* getMainPointer();
        
        //! Renvoie un pointeur vers l'Editor.
        /** \return Un pointer vers cet Editor utilisé.*/
        Editor* getEditor();
        
        //! Renvoie un pointeur vers la zone actuelle
        /** \return Un pointer vers la zone actuellement utilisé.*/
        Zone* getCurrentZone();
        
        //! Nous indique si le nom est deja pris
        /** \return true si il est pris, false autrement */
        bool isNameTaken(std::string name);
        
        //! Exporte toutes les donnees */
        void exportData();
        
        //! Importe toutes les donnees */
        void importData();
        
        //! Importe toutes les zones */
        void importZone(rapidxml::xml_node<> *zone_node);

    private:
        std::vector<Zone*> zone_array;
        Zone* current_zone;
        Pointer* main_pointer;
};



#endif	/* EDITOR_H */

