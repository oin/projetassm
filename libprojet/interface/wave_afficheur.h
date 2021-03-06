#if !defined(WAVE_AFFICHEUR_H_U0C3RQCW)
#define WAVE_AFFICHEUR_H_U0C3RQCW

#include "effet.h"
#include "apercu_son.h"
#include <gtkmm.h>
#include <cairomm/context.h>

struct distributeur_de_teintes {
	static distributeur_de_teintes& instance() { 
		static distributeur_de_teintes inst;
		return inst;
	}
	virtual ~distributeur_de_teintes() {}
	distributeur_de_teintes(const distributeur_de_teintes&);
	void operator=(const distributeur_de_teintes&);
	double prochaine_teinte();
	
private:
	distributeur_de_teintes() {}
};

class controleur;

struct wave_afficheur : public Gtk::DrawingArea {
	wave_afficheur(controleur& c, effet* e, int numero_effet, double pas = 3);
	virtual ~wave_afficheur();
	
	void dessiner(Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int w, int h);
	void dessiner(Cairo::RefPtr<Cairo::Context> &cr, double debut, double fin, int x, int y, int w, int h);
	virtual bool on_expose_event(GdkEventExpose* e);
	virtual bool on_button_press_event(GdkEventButton* e);
	virtual bool on_button_release_event(GdkEventButton* e);	
	virtual bool on_motion_notify_event(GdkEventMotion* e);
	
	void peut_selectionner(bool b) { peut_selectionner_ = b; }
	bool peut_selectionner() { return peut_selectionner_; }
	
	double selection_start() { return selection_start_; }
	double selection_end() { return selection_end_; }
	
	double teinte() { return teinte_selection_; }
	Gdk::Color couleur();
	
	void set_numero(int n) {
		numero_effet_ = n;
	}
private:
	void verifier_selection();
	
	controleur& c_;
	apercu_son& s_;
	double pas_x_;
	double selection_start_, selection_end_;
	bool selectionne_;
	bool peut_selectionner_;
	bool en_plein_clic_sur_croix_;
	double teinte_selection_;
	effet* fx_;
	int numero_effet_;
	static const double rayon_ = 6.0;
};

#endif /* end of include guard: WAVE_AFFICHEUR_H_U0C3RQCW */
