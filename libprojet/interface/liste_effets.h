#if !defined(LISTE_EFFETS_H_1II9TGY3)
#define LISTE_EFFETS_H_1II9TGY3

#include <gtkmm.h>

class controleur;

struct liste_effets : public Gtk::ScrolledWindow {
	liste_effets(controleur& c);
	virtual ~liste_effets() {}
public:
	controleur& c_;
	Gtk::HButtonBox boite_a_boutons_;
	Gtk::Button b_delay_, b_distorsion_, b_normalisation_, b_inverse_, b_volume_, b_chuchotement_, b_vinyl_, b_bassboost_, b_lowpass_, b_highpass_, b_accompagnement_;
};

#endif /* end of include guard: LISTE_EFFETS_H_1II9TGY3 */
