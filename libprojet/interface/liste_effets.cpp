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
	
	b_bassboost_.set_label("Bass boost");
	b_bassboost_.set_focus_on_click(false);
	b_bassboost_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_bassboost));
	boite_a_boutons_.add(b_bassboost_);
	
	b_lowpass_.set_label("Passe-bas");
	b_lowpass_.set_focus_on_click(false);
	b_lowpass_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_lowpass));
	boite_a_boutons_.add(b_lowpass_);
	
	b_highpass_.set_label("Passe-haut");
	b_highpass_.set_focus_on_click(false);
	b_highpass_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_highpass));
	boite_a_boutons_.add(b_highpass_);
	
	b_accompagnement_.set_label("Accompagnement");
	b_accompagnement_.set_focus_on_click(false);
	b_accompagnement_.signal_clicked().connect(sigc::mem_fun(c_, &controleur::creer_accompagnement));
	boite_a_boutons_.add(b_accompagnement_);
	
	add(boite_a_boutons_);
	set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_NEVER);
}