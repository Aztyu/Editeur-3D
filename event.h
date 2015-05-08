/* 
 * File:   event.h
 * Author: Aztyu
 *
 * Created on 21 décembre 2014, 11:33
 */

#ifndef EVENT_H
#define	EVENT_H

#include "Editor.h"
 
//! Classe qui gere tous les evenements du programme
class CEventReceiver : public irr::IEventReceiver{
 
    public:
        //! Constructeur de base.
        /** \param editor Pointeur vers l'Editor actuellement en usage.*/
        CEventReceiver(Editor* editor);
        
        //! Reçoit les evenement envoye par Irrlicht.
        /** \param event Evenement envoye par Irrlicht.
            \return True si traité, False sinon*/
        virtual bool OnEvent(const irr::SEvent &event);
        
        //! Gere les changements des combo box.
        /** \param combo Pointeur vers la combo box touchée par l'évènement.*/
        void OnObjectSelected(irr::gui::IGUIComboBox* combo);
        
        //! Gere les clics dans les menus.
        /** \param menu Pointeur vers le menu touchée par l'évènement.*/
        void OnMenuItemSelected(irr::gui::IGUIContextMenu* menu);
        
        //! Gere les clics dans la fenêtre "Outil".
        /** \param id ID de l'élèment touchée par l'évènement.*/
        void OnToolBoxItemSelected(irr::s32 id);
        
        //! Gere les clics sur les boutons de création d'objet.
        /** \param id ID du bouton de création.*/
        void OnObjectCreation(irr::s32 id);
        
        //! Gere les modifications des valeurs de la fenetre "Outils".
        /** \param editbox Pointeur vers l'editbox touchée par l'évènement.*/
        void OnValueChanged(irr::gui::IGUIEditBox* editbox);
        
        //! Fait tourner la camera vers la droite.
        void angleCameraRight();
        
        //! Fait tourner la camera vers la gauche.
        void angleCameraLeft();
        
        //! Fait avancer la camera.
        void forwardCamera();
        
        //! Fait reculer la camera.
        void backwardCamera();
        
    private:
        Editor* current_editor;
        GraphicalInterface* custom_gui;
};

#endif	/* EVENT_H */

