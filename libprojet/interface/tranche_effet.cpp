#include "tranche_effet.h"
#include "controleur.h"

tranche_effet::tranche_effet(controleur& c, effet* e, int numero_effet) : c_(c), e_(e), numero_effet_(numero_effet), afficheur_(c, e, numero_effet), lbl_wet_("Dry/Wet :"), scl_wet_(0.00, 1.05, 0.05) {
	conteneur_.set_label("Effet");
	
	scl_wet_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_effet::drywet));
	scl_wet_.set_value(1.0);
	
	box_wet_.pack_start(lbl_wet_, false, false, 5);
	box_wet_.pack_start(scl_wet_, true, true, 5);
	
	gauche_.pack_start(box_wet_, false, false, 5);
	
	conteneur_.add(gauche_);
	pack_start(conteneur_, true, true, 5);
	pack_start(afficheur_, true, true, 5);
}

void tranche_effet::drywet() {
	if(e_ != 0)
		e_->wet(scl_wet_.get_value());
}