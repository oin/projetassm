#include "wave_afficheur.h"
#include "hsl2rgb.h"
#include "controleur.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

double modul(double l) {
	while(l < 0.0 || l > 1.0) {
		if(l < 0)
			l += 1.0;
		if(l > 1.0)
			l -= 1.0;
	}
	return l;
}

double distributeur_de_teintes::prochaine_teinte() {
	static double hue_precedente = 0.0;
	double hue = hue_precedente;
	static const double epsilon = 0.2;
	double a = modul(hue_precedente - epsilon);
	double b = modul(hue_precedente + epsilon);
	while(!((b < a && b < hue && hue < a) || (a < b && (hue < a || b < hue)))) {
		hue = static_cast<double>(rand() % 100) / 100;
	}
	
	hue_precedente = hue;

	return hue;
}

wave_afficheur::wave_afficheur(controleur& c, effet* e, int numero_effet, double pas) : c_(c), s_(c.apercu()), pas_x_(pas), selectionne_(false), peut_selectionner_(true), teinte_selection_(distributeur_de_teintes::instance().prochaine_teinte()), fx_(e), numero_effet_(numero_effet) {
	selection_start_ = -1;
	selection_end_ = -1;
	
	if(fx_ != 0 && peut_selectionner_) {
		selection_start_ = fx_->debut();
		selection_end_ = fx_->fin();
	}
	
	add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);
}

wave_afficheur::~wave_afficheur() {}

void wave_afficheur::dessiner(Cairo::RefPtr<Cairo::Context> &cr, int x, int y, int w, int h) {
	dessiner(cr, 0, 1, x, y, w, h);
}

void wave_afficheur::dessiner(Cairo::RefPtr<Cairo::Context> &cr, double debut, double fin, int x, int y, int w, int h) {
	if(debut > fin)
		std::swap(debut, fin);
	fin = std::min(1.0, fin);
	
	size_t nb_traits = static_cast<size_t>(std::ceil(w * 1.0 / pas_x_));
	
	double pas_apercu = s_.nb_points_ * 1.0 / nb_traits;
	
	cr->save();
	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(pas_x_);
	
	size_t trait_debut = static_cast<size_t>(std::floor(debut * nb_traits));
	size_t trait_fin = static_cast<size_t>(std::floor(fin * nb_traits));
	for(size_t i = trait_debut; i < trait_fin; ++i) {
		double n = i * 1.0 / (trait_fin - trait_debut);
		Gdk::Color clr_actuelle = c_.couleur_sur(n, numero_effet_);
		cr->set_source_rgba(clr_actuelle.get_red_p(), clr_actuelle.get_green_p(), clr_actuelle.get_blue_p(), 0.7);
		size_t i_apercu = static_cast<size_t>(std::floor(i * pas_apercu));
		size_t isuiv_apercu = static_cast<size_t>(std::floor((i+1) * pas_apercu));
		double y = std::abs(*std::max_element(s_().begin() + std::min(i_apercu, s_.size() - 1), s_().begin() + std::min(isuiv_apercu, s_.size())));
		cr->move_to(i * pas_x_, (1 - y) * h/2);
		cr->line_to(i * pas_x_, (1 + y) * h/2);
		cr->stroke();
	}
	
	cr->restore();
}

bool wave_afficheur::on_expose_event(GdkEventExpose* e) {
	Glib::RefPtr<Gdk::Window> fenetre = get_window();
	if(fenetre) {
		Cairo::RefPtr<Cairo::Context> cr = fenetre->create_cairo_context();
		
		// Vide le contexte
		cr->rectangle(0, 0, get_width(), get_height());
		cr->clip();
		
		// Dessine des bouts de forme d'onde
		//cr->set_source_rgba(1.0, 0.3, 0.3, 1.0);
		dessiner(cr, 0, 1.0, 0, 0, get_width(), get_height());
		
		// Dessine une sélection
		if(selection_start_ != -1) {
			cr->rectangle(selection_start_ * get_width(), 0, (selection_end_ - selection_start_) * get_width(), get_height());
			Gdk::Color couleur_selection = couleur();
			Gdk::Color couleur_fonce = couleur_hsl(teinte_selection_, 1.0, 0.3);
			cr->set_source_rgba(couleur_selection.get_red_p(), couleur_selection.get_green_p(), couleur_selection.get_blue_p(), 0.5);
			cr->fill_preserve();
			
			cr->set_source_rgba(couleur_fonce.get_red_p(), couleur_fonce.get_green_p(), couleur_fonce.get_blue_p(), 1.0);
			cr->set_line_width(1.0);
			cr->stroke();
		}
		
		// Dessine une croix de fermeture
		if(peut_selectionner_) {
			static const double rayon = 4.0;
			cr->save();
			cr->set_source_rgba(0.0, 0.0, 0.0, 0.8);
			cr->arc(get_width() - rayon * 2.0, rayon, rayon, 0.0, 2.0 * M_PI);
			cr->fill();
			cr->restore();
		}
	}

	return true;
}

Gdk::Color wave_afficheur::couleur() {
	return couleur_hsl(teinte_selection_, 1.0, 0.7);
}

bool wave_afficheur::on_button_press_event(GdkEventButton* e) {
	if(!peut_selectionner_) return true;
	selection_start_ = std::max(0.0, e->x / get_width());
	selectionne_ = true;
	return true;
}

bool wave_afficheur::on_button_release_event(GdkEventButton* e) {
	if(!peut_selectionner_) return true;
	verifier_selection();
	
	if(fx_ != 0) {
		fx_->debut(selection_start_);
		fx_->fin(selection_end_);
	}
	
	c_.actualiser();
	
	selectionne_ = false;
	return true;
}

bool wave_afficheur::on_motion_notify_event(GdkEventMotion* e) {
	if(!peut_selectionner_) return true;
	if(selectionne_) {
		selection_end_ = std::max(0.0, std::min(e->x * 1.0 / get_width(), 1.0));
		queue_draw();
	}
	
	return true;
}

void wave_afficheur::verifier_selection() {
	if(selection_start_ > selection_end_)
		std::swap(selection_start_, selection_end_);
	if(selection_end_ - selection_start_ <= 0.01)
		selection_start_ = -1;
	if(selection_end_ > 1)
		selection_end_ = 1;
	if(selection_start_ < 0)
		selection_start_ = 0;
}