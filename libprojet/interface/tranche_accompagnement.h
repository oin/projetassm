#if !defined(TRANCHE_ACCOMPAGNEMENT_H_HO5O9I29)
#define TRANCHE_ACCOMPAGNEMENT_H_HO5O9I29

#include "tranche_effet.h"

struct tranche_accompagnement : public tranche_effet {
	tranche_accompagnement(controleur&, effet*, int);
	~tranche_accompagnement() {}
	
	void intolchg();
private:
	Gtk::HBox box_intolerance_;
	Gtk::Label lbl_intolerance_;
	Gtk::HScale scl_intolerance_;
};

#endif /* end of include guard: TRANCHE_ACCOMPAGNEMENT_H_HO5O9I29 */
