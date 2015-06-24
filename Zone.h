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
        /** \param base_object Pointeur vers le premier objet de ce groupe. */
        void createGroupObject(SingleObject* base_object=NULL);
        
        void addToGroup(int index);
        
        void importToGroup(int index);
        
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
        
        //! Deselectionne tout objet dans cette zone.
        void unselectAll();
        
        void sendSingleObjectUpdate();
        
        void sendGroupObjectUpdate();
        
        //! Exporte tout objet dans cette zone.
        void exportZone(TiXmlElement* root);
        
        void printZone();
        
        //! Importe l'objet contenu dans un noeud xml.
        void importObject(rapidxml::xml_node<> *object_node);
        
        //! Importe le groupe contenu dans un noeud xml.
        void importGroup(rapidxml::xml_node<> *group_node);
        
        //! Enregistre l'etat actuel de la camera.
        void saveCamera();
        
        //! Charge le dernier etat enregistré de la caméra.
        void loadCamera();
        
        //! Vérifie si le nom de SingleObject est déjà pris.
        bool isSingleObjectNameTaken(std::string name);
        
        //! Vérifie si le nom de GroupObject est déjà pris.
        bool isGroupObjectNameTaken(std::string name);
        
        //! Change la visibilite de la Zone et les GroupObject.
        /** \param isVisible booleen qui definit la visibilite ou non.*/
        void setZoneVisible(bool isVisible);
        
        void resetChild();

    private:
        //! Le vector qui contient les pointeurs vers tous les SingleObject.
        std::vector<SingleObject*> single_object_array;
        
        //! Le vector qui contient les pointeurs vers tous les GroupObject.
        std::vector<GroupObject*> group_object_array;
        
        //! Pointeur vers le SingleObject sélectionné, NULL sinon.
        SingleObject* selected_object;
        
         //! Pointeur vers le GroupObject sélectionné, NULL sinon.
        GroupObject* selected_group;
        
        //! Pointeur vers la structure Pointers du programme.
        Pointer* current_pointer;
        
        //! Contient la rotation de la caméra.
        irr::core::vector3df camera_rotation;
        
        //! Contient la position de la caméra.
        irr::core::vector3df camera_position;
        
        //! Le pointeur vers l'élèment Irrlicht constituant la Zone.
        irr::scene::ISceneNode* zone_mesh;
        
        //! Le nom de la Zone.
        std::string zone_name;
};


#endif	/* ZONE_H */

