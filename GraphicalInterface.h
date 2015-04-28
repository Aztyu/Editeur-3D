/* 
 * File:   GraphicalInterface.h
 * Author: Aztyu
 *
 * Created on 19 avril 2015, 16:48
 */

#include "SingleObjet.h"
#include "GroupObject.h"

#ifndef GRAPHICALINTERFACE_H
#define	GRAPHICALINTERFACE_H


//! Enumeration pour les elements de l'interface
enum Gui{                  //Ajoutez les ids utilises dans le GUI ici
    GUI_ID_SQUARE,                          /**< Creation d'un cube. */
    GUI_ID_RECTANGLE,                       /**< Creation d'un carré(2D). */
    GUI_ID_LINE,                            /**< Creation d'une ligne(2D). */
    GUI_ID_TRAPEZE,                         /**< Creation d'un trapeze(2D). */
    GUI_ID_SPHERE,                          /**< Creation d'une sphere. */
    GUI_ID_PYRAMID,                         /**< Creation d'une pyramide. */
    GUI_ID_CIRCLE,                          /**< Creation d'un cercle(2D). */
    GUI_ID_CYLINDER,                        /**< Creation d'un cylindre. */

    GUI_ID_SINGLE_OBJECT_COMBO_BOX,         /**< combobox pour objet simple. */
    GUI_ID_GROUP_OBJECT_COMBO_BOX,          /**< combobox pour groupe d'objets. */

    GUI_ID_FILE,                            /**< element "Fichier". */
    GUI_ID_NEW,                             /**< element "Nouveau". */
    GUI_ID_LOAD,                            /**< element "Charger". */
    GUI_ID_SAVE,                            /**< element "Sauvegarder". */
    GUI_ID_QUIT,                            /**< element "Quitter". */
    
    GUI_ID_SETTINGS,                        /**< element "Reglages". */
    GUI_ID_SKYBOX,                          /**< element "Skybox". */
    GUI_ID_TOOLBOX,                         /**< element "Boite a outils". */
    
    GUI_ID_HELP,                            /**< element "Aide". */
    GUI_ID_DOC,                             /**< element "Documentation". */
    GUI_ID_ABOUT,                            /**< element "A propos". */
            
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
    
    GUI_ID_OBJECT_WINDOW_GROUP_BOX,         /**< gros plus de debug. */
    GUI_ID_OBJECT_WINDOW_ADD_TO_GROUP,      /**< fenetre d'outils. */
    GUI_ID_OBJECT_WINDOW_ADD_TO__NEW_GROUP  /**< enum value TVal1. */
};


//! Classe qui gere tout l'affichage de l'interface.
class GraphicalInterface {
 
public:
    //! Constructeur par default.
    /** \param gui Pointeur vers l'element GUI d'Irrlicht.
		\param driver Pointeur vers le gestionnaire video d'Irrlicht.
		\param skybox Pointeur vers la skybox. */
    GraphicalInterface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver, irr::scene::ISceneNode* skybox);
    
    //! Destructeur par default.
    virtual ~GraphicalInterface();
    
    //! Appelle la fonction drawAll de Irrlicht.
    void drawAll();
    
    //! Mets a jour la combobox des SingleObject.
    void updateSingleObject(std::vector<SingleObjet*>* tableau);
    void setSingleObjetSelected(int index);
    void updateGroupObject(std::vector<GroupObject*>* tableau);
    void setGroupObjetSelected(int index);
    irr::gui::IGUIEnvironment* getGUIEnvironment();
    void updateWindow(Object* object = NULL);
    irr::scene::ISceneNode* getSkybox();
    Object* getTargetObject();
    bool isInWindow(irr::core::vector2di position);
    
private:
    irr::gui::IGUIContextMenu* menu;
    irr::gui::IGUIComboBox* single_object_box;
    irr::gui::IGUIComboBox* group_object_box;
    irr::scene::ISceneNode* skybox;
    
    irr::video::IVideoDriver* driver;
    irr::gui::IGUIEnvironment* gui;
    irr::gui::IGUIWindow* window;
    
    Object* current_object;
};

#endif	/* GRAPHICALINTERFACE_H */

