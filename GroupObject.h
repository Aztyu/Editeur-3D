/* 
 * File:   GroupObject.h
 * Author: Aztyu
 *
 * Created on 21 avril 2015, 17:07
 */

#ifndef GROUPOBJECT_H
#define	GROUPOBJECT_H

#include "SingleObject.h"

//! Classe qui est utilise pour creer un groupe d' objet
class GroupObject : public Object{
public:
    //! Constructeur de base.
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec echelle.
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, float total_scale);
    
    //! Constructeur avec position de base.
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
     * 		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. 
     *          \param position Vector3D qui contient la position de l'objet */
    GroupObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, const irr::core::vector3df& position);
    
    //! Destructeur par defaut
    virtual ~GroupObject();
   
    //Select/Unselect
    //! Selectionne tous les objets du groupes en changeant la couleur.
    void selectObject();
    
    //Select/Unselect
    //! Deselectionne tous les objets du groupes en changeant la couleur.
    void unselectObject();
    
    //Gestion des objets du groupe
    //! Ajoute un objet au groupe.
    /** \param object Objet a ajouter. */
    void addMember(SingleObject* object);
    
    //! Supprime un objet du groupe selon sa place dans le vector.
    /** \param index Position de l'objet dans le groupe. */
    void removeMember(int index);
    
    //! Supprime un objet du groupe selon un pointeur de l'objet.
    /** \param objet Pointeur de l'objet du groupe. */
    void removeMember(SingleObject* objet);
    
    //! Nettoie le GroupObject de tous SingleObject étant null
    void removeMember();

    //! Renvoie le type de la classe.
    /** \return Une string qui donne le type. */
    std::string getClassType();
    
    //! Renvoie le type de la classe.
    /** \param windows Pointeur vers un TiXmlElement qui represente la base du fichier Xml de sauvegarde. */
    void exportObject(TiXmlElement* windows);
    
    //! Supprime le scenenode dans Irrlicht, à utiliser seulement si on supprime un seul GroupObject
    void Remove();
    
    //! Indique à tous les enfant de GroupObject de changer leur parent à NULL 
    void updateChild();

private:
    //! vector qui contient les pointeurs vers tous les SingleObject du GroupObject.
    std::vector<SingleObject*> member_object;
};

#endif	/* GROUPOBJECT_H */

