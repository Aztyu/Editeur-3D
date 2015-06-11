/* 
 * File:   Zone.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:50
 */

#ifndef ZONE_H
#define	ZONE_H

#include "GroupObject.h"

class Pointer;

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
		\param pointer Pointer vers la structure de pointeur.
         *      \param obj Pointeur vers le scenenode de la zone. */
        Zone(const char* name, Pointer* pointer, irr::scene::ISceneNode* obj);
        
        //! Destructeur de base.
        virtual ~Zone();
        
        //Creation/Suppression des objets
        //! Rajoute un objet qui existe déjà, à la zone.
        /** \param objet Pointer vers l'objet à ajouter. */
        void addObject(SingleObject* objet);
        
        //! Supprime un objet de la zone selon sa place dans le vector.
        /** \param index Place de l'objet dans le vector single_object_array. */
        void removeSingleObject(int index);
        
        //! Supprime un objet de la zone selon sa place dans le vector.
        /** \param index Place de l'objet dans le vector group_object_array. */
        void removeGroupObject(int index);
        
        //! Supprime un objet de la zone selon un pointeur de l'objet.
        /** \param objet Pointeur de l'objet du groupe. */
        void removeObject(Object* objet);
        
        //! Créer un SingleObjet dans la zone selon une énumération object.
        /** \param form Enumeration qui definit le type d'objet créer. */
        void createSingleObject(object form);
        
        //! Créer un GroupObject dans la zone.
        void createGroupObject();
        
        //! Créer un GroupObject dans la zone.
        void createGroupObject(Object* base_object);
        
        //Recuperation d'information
        //! Recupere le pointeur vers un SingleObject.
        /** \param index Position de l'objet dans le vector single_object_array.
            \return Pointeur vers un SingleObject*/
        SingleObject* getSingleObjectPointer(int index);
        
        //! Recupere le pointeur vers un GroupObject.
        /** \param index Position de l'objet dans le vector group_object_array.
            \return Pointeur vers un GroupObject*/
        GroupObject* getGroupObjectPointer(int index);
        
        //! Recupere le pointeur vers l'objet sélectionné.
        /** \return Pointeur vers l'objet actuellement selectionné, NULL si il n'y en a pas. */
        Object* getSelectedObject();
        
        //! Recupere le pointeur vers le SingleObject sélectionné.
        /** \return Pointeur vers le SingleObject actuellement selectionné, NULL si il n'y en a pas. */
        SingleObject* getSelectedSingleObject();
        
        //! Recupere le pointeur vers le GroupObject sélectionné.
        /** \return Pointeur vers le GroupObject actuellement selectionné, NULL si il n'y en a pas. */
        GroupObject* getSelectedGroupObject();
        
        //! Recupere le pointeur vers la zone actuelle.
        /** \return Pointeur vers cette zone. */
        Zone* getPointer();
        
        //! Recupere le pointeur vers l'ISceneNode de la zone actuelle.
        /** \return Pointeur vers l'ISceneNode . */
        irr::scene::ISceneNode* getMeshPointer();
        
        //! Recupere le nom de la zone actuelle.
        /** \return String contenant le nom de cette zone. */
        std::string getName();
        
        //! Recupere le pointeur vers la zone actuelle.
        /** \return Le nombre d'objet de cette zone. */
        int getObjectCount();
        
        //! Renvoie le pointeur vers le vector de SingleObject.
        /** \return le pointeur vers le vector de SingleObject. */
        std::vector<SingleObject*>* getSingleObjectVector();
        
        //! Renvoie le pointeur vers le vector de GroupObject.
        /** \return le pointeur vers le vector de GroupObject. */
        std::vector<GroupObject*>* getGroupObjectVector();
        
        //Selection d'objets
        
        //! Selectionne un SingleObject dans la zone selon sa position dans le vector.
        /** \param index Position de l'objet dans le vector single_object_array. */
        void setSelectedSingleObject(int index);
        
        //! Selectionne un SingleObject dans la zone selon sa position dans le vector.
        /** \param objet Pointeur vers l'ISceneNode de l'objet que l'on veut selectionner.
         *  \return True si l'objet a été selectionné, False sinon. */
        bool setSelectedSingleObject(irr::scene::ISceneNode* objet);
        
        //! Selectionne un GroupObject dans la zone selon sa position dans le vector.
        /** \param index Position de l'objet dans le vector group_object_array. */
        void setSelectedGroupObject(int index);
        
        //! Selectionne un GroupObject dans la zone selon sa position dans le vector.
        /** \param objet Pointeur vers l'ISceneNode de l'objet que l'on veut selectionner.
         *  \return True si l'objet a été selectionné, False sinon. */
        bool setSelectedGroupObject(irr::scene::ISceneNode* objet);
        
        //! Deselectionne toute objet dans cette zone.
        void unselectAll();
        
        
        //Sauvegarde (en cours)
        void exportZone(TiXmlElement* root);
        void printZone();
        void importObject(rapidxml::xml_node<> *object_node);

    private:
        std::vector<SingleObject*> single_object_array; //Ne pas passer de pointer a objet ca fait tout peter
        std::vector<GroupObject*> group_object_array;
        SingleObject* selected_object;
        GroupObject* selected_group;
        Pointer* current_pointer;
        irr::scene::ISceneNode* zone_mesh;
        std::string zone_name;
        int type_number[9];
};


#endif	/* ZONE_H */

