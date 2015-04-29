/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include "Pointers.h"
#include "GroupObject.h"

//! Enumeration utilise pour lors de la creation d'objets
enum object {
    rectangle,      /**< Énumération du carré(2D). */
    line,           /**< Énumération de la ligne(2D). */
    circle,         /**< Énumération du cercle(2D). */
    trapeze,        /**< Énumération du trapeze(2D). */
    cube,           /**< Énumération du cube. */
    pyramid,        /**< Énumération d'une pyramide. */
    sphere,         /**< Énumération d'une sphere. */
    cylinder,       /**< Énumération du cylindre. */
    group};         /**< Énumération du groupe. */

//! Classe qui est utiliser pour creer une zone contenant des objet et groupes d' objets
class Zone {
    public:
        //! Constructeur de base.
        /** \param name Nom de la zone.
		\param pointer Pointer vers la structure de pointeur. */
        Zone(char* name, Pointer* pointer);
        
        //! Destructeur de base.
        virtual ~Zone();
        
        //Creation/Suppression des objets
        //! Rajoute un objet qui existe déjà, à la zone.
        /** \param objet Pointer vers l'objet à ajouter. */
        void addObjet(SingleObjet* objet);
        
        //! Supprime un objet de la zone selon sa place dans le vector.
        /** \param index Place de l'objet dans le vector. */
        void removeObjet(int index);
        
        //! Supprime un objet de la zone selon un pointeur de l'objet.
        /** \param objet Pointeur de l'objet du groupe. */
        void removeObjet(SingleObjet* objet);
        
        //! Créer un SingleObjet dans la zone selon une énumération object.
        /** \param form Enumeration qui definit le type d'objet créer. */
        void createSingleObjet(object form);
        
        //! Créer un GroupObject dans la zone.
        void createGroupObject();
        
        //Recuperation d'information
        SingleObjet* getSingleObjetPointer(int index);
        GroupObject* getGroupObjectPointer(int index);
        Object* getSelectedObject();
        SingleObjet* getSelectedSingleObject();
        GroupObject* getSelectedGroupObject();
        Zone* getPointer();
        int getObjectCount();
        
        //Selection d'objets
        void setSelectedSingleObject(int index);
        bool setSelectedSingleObject(irr::scene::ISceneNode* objet);
        void setSelectedGroupObject(int index);
        void unselectAll();
        
        
        //Sauvegarde (en cours)
        void exportZone();
        void printZone();

    private:
        std::vector<SingleObjet*> single_object_array; //Ne pas passer de pointer a objet ca fait tout peter
        std::vector<GroupObject*> group_object_array;
        SingleObjet* selected_object;
        GroupObject* selected_group;
        Pointer* current_pointer;
        std::string zone_name;
        int type_number[9];
};


#endif	/* ZONE_H */

