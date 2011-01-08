#if !defined(TRANCHE_VINYL_H_A8PX07J3)
#define TRANCHE_VINYL_H_A8PX07J3

#include "tranche_effet.h"

struct tranche_vinyl : public tranche_effet {
	tranche_vinyl(controleur&, effet*, int);
	~tranche_vinyl() {}
	
	void souffle();
	void clics();
private:
	Gtk::HBox box_souffle_;
	Gtk::Label lbl_souffle_;
	Gtk::HScale scl_souffle_;
	Gtk::HBox box_clics_;
	Gtk::Label lbl_clics_;
	Gtk::HScale scl_clics_;
};

#endif /* end of include guard: TRANCHE_VINYL_H_A8PX07J3 */
