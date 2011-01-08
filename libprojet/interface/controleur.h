#if !defined(CONTROLEUR_H_DSQJBJNI)
#define CONTROLEUR_H_DSQJBJNI

#include "liste_effets.h"
#include "tranche_effet.h"

#include "apercu_son.h"
#include <chaine_effets.h>
#include <gtkmm.h>
#include <son.h>
#include <string>

struct controleur {
	controleur(int argc, char** argv);
	virtual ~controleur();
	
	void lancer();
	void appliquer_effets();
	
	void creer_noisegate();
	void creer_delay();
	void creer_distorsion();
	void creer_normalisation();
	void creer_inverse();
	void creer_volume();
	void creer_chuchotement();
	void creer_vinyl();
	
	void ouvrir_fichier_entree();
	void choisir_fichier_sortie();
	
	apercu_son& apercu() { return apercu_; }
	void actualiser();
	
	Gdk::Color couleur_sur(double position, int jusqu_a);
	
	void supprimer_effet(int numero);
private:
	void charger_son(std::string);
	
	Gtk::Main gtk_;
	Gtk::Window w_;
	Gtk::VBox vbx_principale_;
	Gtk::HBox hbx_bas_;
	Gtk::HButtonBox btns_bas_;
	Gtk::Button btn_appliquer_, btn_entree_, btn_sortie_;
	Gtk::ScrolledWindow scl_effets_;
	Gtk::VBox vbx_effets_;
	liste_effets liste_;
	assm::son s_;
	apercu_son apercu_;
	chaine_effets fx_;
	wave_afficheur aff_entree_, aff_sortie_;
	Gtk::HBox hbx_entree_, hbx_sortie_, hbx_entree_fichier_, hbx_sortie_fichier_;
	Gtk::VBox vbx_entree_gauche_, vbx_sortie_gauche_;
	Gtk::Label lbl_entree_fichier_, lbl_sortie_fichier_;
	Gtk::Frame frm_entree_, frm_sortie_;
	std::string nom_fichier_out_;
	
	std::vector<tranche_effet*> tranches_;
};

#endif /* end of include guard: CONTROLEUR_H_DSQJBJNI */
