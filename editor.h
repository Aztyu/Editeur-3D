/* 
 * File:   editor.h
 * Author: Aztyu
 *
 * Created on 26 décembre 2014, 11:29
 */

#ifndef EDITOR_H
#define	EDITOR_H

#include "Zone.h"

//! Classe de base qui contient toutes les zones et la plupart des informations
class Editor {
    public:
        //! Constructeur de base.
        /** \param struct_pointer Pointeur vers la structure Pointers.*/
        Editor(Pointer* struct_pointer);
        
        //! Destructeur de base.
        virtual ~Editor();
        
        //Gestion des zones
        //! Creer une zone.
        /** \param name Le nom de la zone à créer.*/
        void createZone(char* name);
        
        //! Definit la zone actuelle.
        /** \param zone Pointeur vers la zone à définir comme actuelle.*/
        void setCurrentZone(Zone* zone);
        
        //! Definit le Pointers utilisé dans le programme.
        /** \param struct_pointer Pointeur vers le Pointers à utiliser.*/
        void setMainPointer(Pointer* struct_pointer);
        
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
        
    private:
        std::vector<Zone*> zone_array;
        Zone* current_zone;
        Pointer* main_pointer;
};

#endif	/* EDITOR_H */

