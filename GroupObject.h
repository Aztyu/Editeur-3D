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
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet. */
    GroupObject(irr::scene::ISceneNode* objet, const char* name);
    
    //! Constructeur avec echelle.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet. */
    GroupObject(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    
    //! Constructeur avec position de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     * 		\param name Le nom desire pour l'objet. */
    GroupObject(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    
    //! Constructeur avec echelle et position.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     *          \param total_scale Un entier qui indique l'echelle de l'objet.
     * 		\param name Le nom desire pour l'objet. */
    GroupObject(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);
    
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

    //Sauvegarde(en cours)
    friend std::ostream& operator <<(std::ostream stream, SingleObject& obj);
    const char* printObject();
private:
    std::vector<SingleObject*> member_object;
};

#endif	/* GROUPOBJECT_H */

