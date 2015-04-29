/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

#include "Object.h"

//! Classe qui est utilise pour creer un simple objet
class SingleObjet : public Object{
public:
    //! Constructeur de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet. */
    SingleObjet(irr::scene::ISceneNode* objet, const char* name);
    
    //! Constructeur avec echelle.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet. */
    SingleObjet(irr::scene::ISceneNode* objet, float total_scale, const char* name);
    
    //! Constructeur avec position de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     * 		\param name Le nom desire pour l'objet. */
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name);
    
    //! Constructeur avec echelle et position.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     *          \param total_scale Un entier qui indique l'echelle de l'objet.
     * 		\param name Le nom desire pour l'objet. */
    SingleObjet(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name);

    //Selection/Deselection
    //! Selection de l'objet.
    void selectObject();
    
    //! Selection de l'objet par son groupe.
    void groupSelectObject();
    
    //! Deselectionne l'objet dans tout les cas.
    void unselectObject();

    //Sauvegarde (en cours)
    friend std::ostream& operator <<(std::ostream stream, SingleObjet& obj);
    const std::string printObjet();
    
    //Gestion de groupe
    //! Definit l'élèment parent de l'objet(donc le groupe).
    /** \param parent Pointeur vers l'Object qui deviendra le parent. */
    void setParent(Object* parent);
    
    //! Permet de savoir si l'objet est déjà dans un groupe ou non.
    /** \return True si l'objet est dans un groupe, False si l'objet n'est pas dans un groupe. */
    bool hasParent();
    
    //! Recupere le pointeur vers cette objet.
    /** \return Un pointeur vers cette objet */
    SingleObjet* getPointer();
};

#endif	/* SINGLEOBJECT_H */

