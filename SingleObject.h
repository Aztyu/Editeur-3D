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
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *      \param name Le nom desire pour l'objet.
     *      \param parent L'ISceneNode de la Zone.
     *      \param type Une énumération de type oject qui indique la forme de l'objet(Carré, Cylindre, ...). */
    SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, object type);
    
    //! Constructeur avec echelle.
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *      \param name Le nom desire pour l'objet.
     *      \param total_scale Un entier qui indique l'echelle de l'objet. 
     *      \param parent L'ISceneNode de la Zone.
     *      \param type Une énumération de type oject qui indique la forme de l'objet(Carré, Cylindre, ...).*/
    SingleObject(irr::scene::ISceneNode* obj, const char* name, irr::scene::ISceneNode* parent, float total_scale, object type);
    
    //! Constructeur avec position de base.
    /** \param obj Pointeur vers le ISceneNode qui est donne par Irrlicht.
     *      \param name Le nom desire pour l'objet.
     *      \param parent L'ISceneNode de la Zone.
     *      \param position Vector3df qui contient la position voulue.
     *      \param type Une énumération de type oject qui indique la forme de l'objet(Carré, Cylindre, ...). */
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
    void exportObject(TiXmlElement* windows);
    
    //Gestion de groupe
    //! Definit l'élèment parent de l'objet(donc le groupe).
    /** \param new_parent Pointeur vers l'Object qui deviendra le parent. */
    void setParent(Object* new_parent);
    
    //! Permet de savoir si l'objet est déjà dans un groupe ou non.
    /** \return True si l'objet est dans un groupe, False si l'objet n'est pas dans un groupe. */
    bool hasParent();
    
    //! Recupere le pointeur vers cette objet.
    /** \return Un pointeur vers cette objet */
    SingleObject* getPointer();
    
    //! Recupere l'enumeration du type de l'objet.
    /** \return Un enum de type object */
    object getType();
    
    //! Renvoie le type de la classe.
    /** \return Une string qui donne le type. */
    std::string getClassType();
    
    //! Renvoie le pointeur vers le parent du SingleObject.
    /** \return Le pointeur vers l'Object parent. */
    Object* getParent();
    
    //! Renvoie un boolèen qui nous indique si le SingleObject appartient ou non à un groupe.
    /** \return True si le SingleObject est dans un groupe, False sinon. */
    bool isInGroup();
    
private:
    //! Le pointeur vers le parent du SingleObject.
    Object* parent;
    
    //! L'énumération de type object qui nous indique la forme du SingleObject
    object type;
};

#endif	/* SINGLEOBJECT_H */

