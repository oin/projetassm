#if !defined(WAVE_AFFICHEUR_H_U0C3RQCW)
#define WAVE_AFFICHEUR_H_U0C3RQCW

#include "apercu_son.h"
#include <gtkmm.h>
#include <cairomm/context.h>

struct wave_afficheur : public Gtk::DrawingArea {
	wave_afficheur(apercu_son& s, double pas = 3);
	virtual ~wave_afficheur();
	
	void dessiner(Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int w, int h);
	void dessiner(Cairo::RefPtr<Cairo::Context> &cr, double debut, double fin, int x, int y, int w, int h);
	virtual bool on_expose_event(GdkEventExpose* e);
	virtual bool on_button_press_event(GdkEventButton* e);
	virtual bool on_button_release_event(GdkEventButton* e);	
	virtual bool on_motion_notify_event(GdkEventMotion* e);
private:
	apercu_son& s_;
	double pas_x_;
	double selection_start_, selection_end_;
	bool selectionne_;
};

#endif /* end of include guard: WAVE_AFFICHEUR_H_U0C3RQCW */
