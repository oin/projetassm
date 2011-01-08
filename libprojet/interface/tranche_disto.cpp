#include "tranche_disto.h"
#include "controleur.h"
#include <distorsion.h>

tranche_disto::tranche_disto(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet), lbl_gain_("Gain :"), scl_gain_(0.0, 50.0, 0.1) {
	conteneur_.set_label("Distorsion");
	
	scl_gain_.set_value(1.0);
	scl_gain_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_disto::gainchg));
	
	box_gain_.pack_start(lbl_gain_, false, false, 5);
	box_gain_.pack_start(scl_gain_, true, true, 5);
	
	gauche_.pack_start(box_gain_, false, false, 5);
}

void tranche_disto::gainchg() {
	if(e_ != 0)
		static_cast<distorsion*>(e_)->gain(scl_gain_.get_value());
}