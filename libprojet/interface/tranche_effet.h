#if !defined(TRANCHE_EFFET_H_LPQX7IV7)
#define TRANCHE_EFFET_H_LPQX7IV7

#include <effet.h>
#include "wave_afficheur.h"
#include <gtkmm.h>

class controleur;

struct tranche_effet : public Gtk::HBox {
	tranche_effet(controleur&, effet*, int);
	virtual ~tranche_effet() {}
	
	wave_afficheur& afficheur() { return afficheur_; }
	
	void set_numero(int n) {
		numero_effet_ = n;
		afficheur_.set_numero(n);
	}
	void drywet();
protected:
	controleur& c_;
	effet* e_;
	int numero_effet_;
	wave_afficheur afficheur_;
	Gtk::VBox gauche_;
	Gtk::Frame conteneur_;
	Gtk::HBox box_wet_;
	Gtk::Label lbl_wet_;
	Gtk::HScale scl_wet_;
};

#endif /* end of include guard: TRANCHE_EFFET_H_LPQX7IV7 */
