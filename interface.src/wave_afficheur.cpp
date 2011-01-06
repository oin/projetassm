#include "wave_afficheur.h"
#include <algorithm>

wave_afficheur::wave_afficheur(apercu_son& s, double pas) : s_(s), pas_x_(pas), selection_start_(-1), selection_end_(-1) {
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
	
		cr->rectangle(e->area.x, e->area.y, e->area.width, e->area.height);
		cr->clip();
		
		cr->set_source_rgba(0.0, 0.0, 0.0, 0.5);
		//cr->set_source_rgba(1.0, 0.3, 0.3, 1.0);
		dessiner(cr, 0, 0.5, 0, 0, e->area.width, e->area.height);
		//cr->set_source_rgb(0.3, 0.3, 1.0);
		dessiner(cr, 0.5, 1.0, 0, 0, e->area.width, e->area.height);
		
		if(selection_start_ != -1) {
			cr->rectangle(selection_start_ * e->area.width, 0, (selection_end_ - selection_start_) * e->area.width, e->area.height);
			cr->set_source_rgba(1.0, 1.0, 1.0, 0.5);
			cr->fill();
		}
	}

	return true;
}

bool wave_afficheur::on_button_press_event(GdkEventButton* e) {
	selection_start_ = std::max(0.0, e->x / get_width());
	selectionne_ = true;
	return true;
}

bool wave_afficheur::on_button_release_event(GdkEventButton* e) {
	if(selection_end_ - selection_start_ <= 0.01)
		selection_start_ = -1;
	selectionne_ = false;
	return true;
}

bool wave_afficheur::on_motion_notify_event(GdkEventMotion* e) {
	if(selectionne_) {
		selection_end_ = std::min(e->x * 1.0 / get_width(), 1.0);
		queue_draw();
	}
	
	return true;
}