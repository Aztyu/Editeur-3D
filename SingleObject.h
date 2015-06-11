/* 
 * File:   Objet.h
 * Author: Aztyu
 *
 * Created on 22 décembre 2014, 15:06
 */

#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

#include "Object.h"

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
    
//! Classe qui est utilise pour creer un simple objet
class SingleObject : public Object{
public:
    //! Constructeur de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    SingleObject(irr::scene::ISceneNode* objet, const char* name, irr::scene::ISceneNode* parent, object type);
    
    //! Constructeur avec echelle.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet. 
                \param parent L'ISceneNode de la Zone.*/
    SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, float total_scale, object type);
    
    //! Constructeur avec position de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     * 		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, irr::core::vector3df position, object type);
    

    //! Destructeur de base.
    ~SingleObject();
    
    //Selection/Deselection
    //! Selection de l'objet.
    void selectObject();
    
    //! Selection de l'objet par son groupe.
    void groupSelectObject();
    
    //! Deselectionne l'objet dans tout les cas.
    void unselectObject();
    
    //! Exporte tous les objets
    void exportObject(TiXmlElement* root);

    //Sauvegarde (en cours)
    friend std::ostream& operator <<(std::ostream stream, SingleObject& obj);
    const std::string printObject();
    
    //Gestion de groupe
    //! Definit l'élèment parent de l'objet(donc le groupe).
    /** \param parent Pointeur vers l'Object qui deviendra le parent. */
    void setParent(Object* parent);
    
    //! Permet de savoir si l'objet est déjà dans un groupe ou non.
    /** \return True si l'objet est dans un groupe, False si l'objet n'est pas dans un groupe. */
    bool hasParent();
    
    //! Recupere le pointeur vers cette objet.
    /** \return Un pointeur vers cette objet */
    SingleObject* getPointer();
    
    //! Recupere l'enumeration du type de l'objet.
    /** \return Un enum de type object */
    object getType();
    
private:
    Object* parent;
    object type;
};

#endif	/* SINGLEOBJECT_H */

