#include "liste_effets.h"
#include "controleur.h"

liste_effets::liste_effets(controleur& c) : c_(c), boite_a_boutons_(Gtk::BUTTONBOX_START) {
	b_volume_.set_label("Volume");
	b_volume_.set_focus_on_click(false);
	b_volume_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_volume));
	boite_a_boutons_.add(b_volume_);
	
	b_inverse_.set_label("Inversion");
	b_inverse_.set_focus_on_click(false);
	b_inverse_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_inverse));
	boite_a_boutons_.add(b_inverse_);
	
	b_noisegate_.set_label("Porte de bruit");
	b_noisegate_.set_focus_on_click(false);
	b_noisegate_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_noisegate));
	boite_a_boutons_.add(b_noisegate_);
	
	b_delay_.set_label("Écho");
	b_delay_.set_focus_on_click(false);
	b_delay_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_delay));
	boite_a_boutons_.add(b_delay_);
	
	b_normalisation_.set_label("Normalisation");
	b_normalisation_.set_focus_on_click(false);
	b_normalisation_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_normalisation));
	boite_a_boutons_.add(b_normalisation_);
	
	b_distorsion_.set_label("Distorsion");
	b_distorsion_.set_focus_on_click(false);
	b_distorsion_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_distorsion));
	boite_a_boutons_.add(b_distorsion_);
	
	b_chuchotement_.set_label("Chuchotement");
	b_chuchotement_.set_focus_on_click(false);
	b_chuchotement_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_chuchotement));
	boite_a_boutons_.add(b_chuchotement_);
	
	b_vinyl_.set_label("Vinyl");
	b_vinyl_.set_focus_on_click(false);
	b_vinyl_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_vinyl));
	boite_a_boutons_.add(b_vinyl_);
	
	add(boite_a_boutons_);
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_NEVER);
}