#if !defined(TRANCHE_DISTO_H_GWZN8DMQ)
#define TRANCHE_DISTO_H_GWZN8DMQ

#include "tranche_effet.h"

struct tranche_disto : public tranche_effet {
	tranche_disto(controleur&, effet*, int);
	~tranche_disto() {}
	
	void gainchg();
private:
	Gtk::HBox box_gain_;
	Gtk::Label lbl_gain_;
	Gtk::HScale scl_gain_;
};

#endif /* end of include guard: TRANCHE_DISTO_H_GWZN8DMQ */
