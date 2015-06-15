/* 
 * File:   GraphicalInterface.h
 * Author: Aztyu
 *
 * Created on 19 avril 2015, 16:48
 */

#ifndef GRAPHICALINTERFACE_H
#define	GRAPHICALINTERFACE_H

#include "Zone.h"
#include "Pointers.h"
//! Enumeration pour les elements de l'interface
enum Gui{                  //Ajoutez les ids utilises dans le GUI ici
    GUI_ID_CUBE,                          /**< Creation d'un cube. */
    GUI_ID_SQUARE,                       /**< Creation d'un carré(2D). */
    GUI_ID_LINE,                            /**< Creation d'une ligne(2D). */
    GUI_ID_TRAPEZE,                         /**< Creation d'un trapeze(2D). */
    GUI_ID_SPHERE,                          /**< Creation d'une sphere. */
    GUI_ID_PYRAMID,                         /**< Creation d'une pyramide. */
    GUI_ID_CIRCLE,                          /**< Creation d'un cercle(2D). */
    GUI_ID_CYLINDER,                        /**< Creation d'un cylindre. */

    GUI_ID_SINGLE_OBJECT_COMBO_BOX,         /**< combobox pour objet simple. */
    GUI_ID_GROUP_OBJECT_COMBO_BOX,          /**< combobox pour groupe d'objets. */
    GUI_ID_ZONE_COMBO_BOX,                   /**< combobox pour les zones. */

    GUI_ID_FILE,                            /**< element "Fichier". */
    GUI_ID_NEW,                             /**< element "Nouveau". */
    GUI_ID_LOAD,                            /**< element "Charger". */
    GUI_ID_SAVE,                            /**< element "Sauvegarder". */
    GUI_ID_QUIT,                            /**< element "Quitter". */
    
    GUI_ID_NEW_ZONE,                        /**< element "Nouveau"-"Zone". */
    GUI_ID_NEW_GROUP,                       /**< element "Nouveau"-"Group". */
    
    GUI_ID_SETTINGS,                        /**< element "Reglages". */
    GUI_ID_SKYBOX,                          /**< element "Skybox". */
    GUI_ID_TOOLBOX,                         /**< element "Boite a outils". */
    
    GUI_ID_HELP,                            /**< element "Aide". */
    GUI_ID_DOC,                             /**< element "Documentation". */
    GUI_ID_ABOUT,                            /**< element "A propos". */
    
    GUI_ID_INFORMATIONS,                    /**<fenetre d'information. */
    GUI_ID_INFORMATIONS_RESET_CAMERA,
    GUI_ID_INFORMATIONS_DELETE_ZONE,
    
    GUI_ID_OBJECT_WINDOW,                   /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_OBJECT_NAME,       /**< nom de l'objet. */
    
    GUI_ID_OBJECT_WINDOW_POSITION_X_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_POSITION_X_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_POSITION_X_DOWN,   /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_POSITION_Y_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_POSITION_Y_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_POSITION_Y_DOWN,   /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_POSITION_Z_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_POSITION_Z_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_POSITION_Z_DOWN,   /**< enum value TVal1. */
    
    GUI_ID_OBJECT_WINDOW_ROTATION_X_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_ROTATION_X_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_ROTATION_X_DOWN,   /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Y_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Y_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Y_DOWN,   /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Z_UP,     /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Z_VALUE,  /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_ROTATION_Z_DOWN,   /**< enum value TVal1. */
    
    GUI_ID_OBJECT_WINDOW_SCALE_X_UP,        /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_SCALE_X_VALUE,     /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_SCALE_X_DOWN,      /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_SCALE_Y_UP,        /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_SCALE_Y_VALUE,     /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_SCALE_Y_DOWN,      /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_SCALE_Z_UP,        /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_SCALE_Z_VALUE,     /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_SCALE_Z_DOWN,      /**< enum value TVal1. */
    GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_UP,    /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_SCALE_TOTAL_DOWN,  /**< enum value TVal1. */
    
    GUI_ID_OBJECT_WINDOW_ADD_TO_GROUP,      /**< Ajoute l'objet groupe selectionne. */
    GUI_ID_OBJECT_WINDOW_REMOVE_FROM_GROUP, /**< Enleve l'objet du groupe actuel. */
    GUI_ID_OBJECT_WINDOW_GROUP_COMBO_BOX    /**< Combo box affichant les groupes presents. */
};


//! Classe qui gere tout l'affichage de l'interface.
class GraphicalInterface {
 
public:
    //! Constructeur par defaut.
    /** \param gui Pointeur vers l'element GUI d'Irrlicht.
		\param driver Pointeur vers le gestionnaire video d'Irrlicht.
		\param skybox Pointeur vers la skybox. */
    GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver, irr::scene::ISceneNode* skybox);
    
    //! Destructeur par default.
    virtual ~GraphicalInterface();
    
    //! Appelle la fonction drawAll de Irrlicht.
    void drawAll();
    
    //! Mets a jour la combobox des SingleObject.
    /** \param tableau vector de SingleObject mis a jour pour le transferer */
    void updateSingleObject(std::vector<SingleObject*>* tableau);
    
    //! Selectionne un SingleObject specifique dans la combo box.
    /** \param index Index de l'objet dans la combo box.*/
    void setSingleObjectSelected(int index);
    
    //! Mets a jour la combo box qui contient les groupes.
    /** \param tableau vector de GroupObject mis a jour pour le transferer */
    void updateGroupObject(std::vector<GroupObject*>* tableau);
    
    //! Mets a jour la combobox des SingleObject.
    /** \param tableau vector de SingleObject mis a jour pour le transferer */
    void updateZone(std::vector<Zone*>* tableau);
    
    //! Selectionne un GroupObject specifique dans la combo box.
    /** \param index Index de l'objet dans la combo box. */
    void setGroupObjectSelected(int index);
    
    //! Selectionne une Zone specifique dans la combo box.
    /** \param index Index de la zone dans la combo box. */
    void setZoneSelected(int index);
    
    //! Recupere un pointeur vers le GUI Environment.
    /** \return Pointeur vers le GUI Environment en cours d'utilisation */
    irr::gui::IGUIEnvironment* getGUIEnvironment();
    
    //! Mets à jour la fenetre Outils.
    /** \param object L'objet qui sera concerne par les modifications dans la fenetre*/
    void updateWindow(Object* object);
    
    //! Mets à jour la fenetre Outils grace a l'attribut current_object.
    void updateWindow();
    
    //! Mets à jour la fenetre Informations grace a l'attribut current_zone.
    void updateInformation(Zone* current_zone);
    
    //! Recupere un pointeur vers l'element skybox.
    /** \return Un pointeur vers un ISceneNode pour pouvoir modifier la skybox */
    irr::scene::ISceneNode* getSkybox();
    
    //! Renvoie l'objet actuellement selectionne.
    /** \return Un pointeur vers l'objet selectionne qui apparait dans la fenetre Outils */
    Object* getTargetObject();
    
    //! Retourne un booleen qui indique si le point est ou non dans la fenetre Outils.
    /** \param position Vector2di qui contient le point a teste.
		\return True si le point est dans la fenetre, False sinon ou si la fenetre néxiste pas. */
    bool isInWindow(irr::core::vector2di position);
    
private:
    irr::gui::IGUIContextMenu* menu;
    irr::gui::IGUIComboBox* single_object_box;
    irr::gui::IGUIComboBox* group_object_box;
    irr::gui::IGUIComboBox* zone_box;
    irr::scene::ISceneNode* skybox;
    
    irr::video::IVideoDriver* driver;
    irr::gui::IGUIEnvironment* gui;
    irr::gui::IGUIWindow* window;
    
    Object* current_object;
};

#endif	/* GRAPHICALINTERFACE_H */

