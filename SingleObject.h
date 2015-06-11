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
class SingleObject : public Object{
public:
    //! Constructeur de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    SingleObject(irr::scene::ISceneNode* objet, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec echelle.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
		\param name Le nom desire pour l'objet.
                \param total_scale Un entier qui indique l'echelle de l'objet. 
                \param parent L'ISceneNode de la Zone.*/
    SingleObject(irr::scene::ISceneNode* objet, float total_scale, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec position de base.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     * 		\param name Le nom desire pour l'objet.
     *          \param parent L'ISceneNode de la Zone. */
    SingleObject(irr::scene::ISceneNode* objet, float x, float y, float z, const char* name, irr::scene::ISceneNode* parent);
    
    //! Constructeur avec echelle et position.
    /** \param objet Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *          \param x Position en x.
     *          \param y Position en y.
     *          \param z Position en z.
     *          \param total_scale Un entier qui indique l'echelle de l'objet.
     * 		\param name Le nom desire pour l'objet. 
                \param parent L'ISceneNode de la Zone.*/
    SingleObject(irr::scene::ISceneNode* objet, float x, float y, float z, float total_scale, const char* name, irr::scene::ISceneNode* parent);

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
    
private:
    Object* parent;
};

#endif	/* SINGLEOBJECT_H */

