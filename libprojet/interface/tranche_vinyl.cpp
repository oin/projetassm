#include "tranche_vinyl.h"
#include "controleur.h"
#include <vinyl.h>

tranche_vinyl::tranche_vinyl(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet), lbl_souffle_("Souffle :"), scl_souffle_(0.0, 1.01, 0.01), lbl_clics_("Clics :"), scl_clics_(0.0, 100, 1) {
	conteneur_.set_label("Vinyl");
	
	scl_souffle_.set_value(static_cast<vinyl*>(e_)->souffle() * 10);
	scl_souffle_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_vinyl::souffle));
	
	box_souffle_.pack_start(lbl_souffle_, false, false, 5);
	box_souffle_.pack_start(scl_souffle_, true, true, 5);
	
	gauche_.pack_start(box_souffle_, false, false, 5);
	
	
	scl_clics_.set_value(static_cast<vinyl*>(e_)->clics());
	scl_clics_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_vinyl::clics));
	
	box_clics_.pack_start(lbl_clics_, false, false, 5);
	box_clics_.pack_start(scl_clics_, true, true, 5);
	
	gauche_.pack_start(box_clics_, false, false, 5);
}

void tranche_vinyl::souffle() {
	if(e_ != 0)
		static_cast<vinyl*>(e_)->souffle(scl_souffle_.get_value() / 10);
}

void tranche_vinyl::clics() {
	if(e_ != 0)
		static_cast<vinyl*>(e_)->clics(scl_clics_.get_value());
}