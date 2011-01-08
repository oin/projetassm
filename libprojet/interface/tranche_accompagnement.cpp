#include "tranche_accompagnement.h"
#include "controleur.h"
#include <accompagnement.h>

tranche_accompagnement::tranche_accompagnement(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet), lbl_intolerance_("Intolérance :"), scl_intolerance_(0.0, 100.0, 1.0) {
	conteneur_.set_label("Accompagnement");
	
	scl_intolerance_.set_value(static_cast<accompagnement*>(e_)->intolerance());
	scl_intolerance_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_accompagnement::intolchg));
	
	box_intolerance_.pack_start(lbl_intolerance_, false, false, 5);
	box_intolerance_.pack_start(scl_intolerance_, true, true, 5);
	
	gauche_.pack_start(box_intolerance_, false, false, 5);
}

void tranche_accompagnement::intolchg() {
	if(e_ != 0)
		static_cast<accompagnement*>(e_)->intolerance(scl_intolerance_.get_value());
}