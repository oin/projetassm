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

struct wave_afficheur : public Gtk::DrawingArea {
	wave_afficheur(apercu_son& s, effet& e, double pas = 3);
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
private:
	apercu_son& s_;
	double pas_x_;
	double selection_start_, selection_end_;
	bool selectionne_;
	bool peut_selectionner_;
	double teinte_selection_;
	effet& fx_;
};

#endif /* end of include guard: WAVE_AFFICHEUR_H_U0C3RQCW */
