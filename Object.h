/* 
 * File:   Object.h
 * Author: Aztyu
 *
 * Created on 21 avril 2015, 17:07
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <iostream>
#include "irrlicht.h"
#include <vector>

//! Classe de base pour SIngleObject et GroupObject, gere les ISceneNodes natif a Irrlicht
class Object {
public:
    //! Constructeur de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone.  */
    Object(irr::scene::ISceneNode* objet, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec echelle.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet.
     *          \param parent L'ISceneNode de la Zone.  */
    Object(irr::scene::ISceneNode* objet, float total_scale, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec position de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     * 		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    Object(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec echelle et position.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     *          \param total_scale Un entier qui indique l'echelle de l'objet.
     * 		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    Object(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name, irr::scene::ISceneNode* parent);
    
    //! Destructeur par defaut
    virtual ~Object();
    
    //Modification de l'objet
    //! Change la position de l'objet pour celle passee en parametre.
    /** \param x Position en x par rapport a l'origine.
     *          \param y Position en y par rapport a l'origine.
     *          \param z Position en z par rapport a l'origine. */
    void setPosition(float x, float y, float z);
    
    //! Change l'echelle de l'objet pour celle passee en parametre.
    /** \param x Echelle x par rapport a l'echelle d'origine.
     *          \param y Echelle y par rapport a l'echelle d'origine.
     *          \param z Echelle z par rapport a l'echelle d'origine. */
    void setScale(float x, float y, float z);
    
    //! Change la rotation de l'objet pour celle passee en parametre.
    /** \param x Rotation en degre sur l'axe x par rapport a la rotation d'origine.
     *          \param y Rotation en degre sur l'axe y par rapport a la rotation d'origine.
     *          \param z Rotation en degre sur l'axe z par rapport a la rotation d'origine. */
    void setRotation(float x, float y, float z);
    
    //! Modifie la position de l'objet par celle passee en parametre.
    /** \param x Decalage en x par rapport a la position actuelle.
     *          \param y Decalage en y par rapport a la position actuelle.
     *          \param z Decalage en z par rapport a la position actuelle. */
    void modifyPositionBy(float x, float y, float z);
    
    //! Modifie la position de l'objet par celle passee en parametre.
    /** \param values Vector3D qui contient le decalage dans toutes les directions par rapport a la position actuelle. */
    void modifyPositionBy(irr::core::vector3df values);
    
    //! Multiplie ou divise l'échelle de l'objet par celle passée en paramètre.
    /** \param x Nombre par laquelle on multiplie(+) ou divise(-) l'échelle en x.
     *          \param y Nombre par laquelle on multiplie(+) ou divise(-) l'échelle en y.
     *          \param z Nombre par laquelle on multiplie(+) ou divise(-) l'échelle en z. */
    void modifyScaleBy(float x, float y, float z);
    
    //! Multiplie ou divise l'échelle de l'objet par celle passée en paramètre.
    /** \param values Vector3D qui contient le nombre par laquelle on multiplie(+) ou divise(-) l'échelle dans toutes les directions. */
    void modifyScaleBy(irr::core::vector3df values);
    
    //! Modifie la rotation de l'objet par celle passee en parametre.
    /** \param x Rotation en degre sur l'axe x par rapport a la rotation actuelle.
     *          \param y Rotation en degre sur l'axe y par rapport a la rotation actuelle.
     *          \param z Rotation en degre sur l'axe z par rapport a la rotation actuelle. */
    void modifyRotationBy(float x, float y, float z);
    
    //! Modifie la rotation de l'objet par celle passee en parametre.
    /** \param values Vector3D qui contient la rotation en degre sur tous les axes par rapport a la rotation actuelle. */
    void modifyRotationBy(irr::core::vector3df values);
    
    //Recuperation des informations
    //! Recupere la position de l'objet
    /** \return Un vector3df qui contient la position de l'objet*/
    const irr::core::vector3df& getPosition();
    
    //! Recupere l'échelle de l'objet
    /** \return Un vector3df qui contient l'échelle de l'objet*/
    const irr::core::vector3df& getScale();
    
    //! Recupere la rotation de l'objet
    /** \return Un vector3df qui contient la rotation de l'objet*/
    const irr::core::vector3df& getRotation();
    
    //! Deselectionne l'objet en changeant la couleur.
    virtual void unselectObject()=0;
    
    //! Selectionne l'objet en changeant la couleur.
    virtual void selectObject()=0;
    
    //Recuperation d'information
    //! Retourne l'ISceneNode contenu dans l'objet
    /** \return Pointeur vers l'ISceneNode(l'objet sous Irrlicht)*/
    irr::scene::ISceneNode* getSceneNode();
    
    //! Retourne le nom de l'objet
    /** \return Le nom de l'objet*/
    std::string getName();
    
protected:
    irr::scene::ISceneNode* objet;
    std::string object_name;
    irr::scene::ISceneNode* default_parent;
};

#endif	/* OBJECT_H */

