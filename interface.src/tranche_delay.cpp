#include "tranche_delay.h"
#include "controleur.h"
#include <delay.h>

tranche_delay::tranche_delay(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet), lbl_time_("Temps (s) :"), scl_time_(0.0, 2.01, 0.01), lbl_feedback_("Feedback"), scl_feedback_(0.0, 1.05, 0.05) {
	scl_wet_.set_value(0.5);
	
	conteneur_.set_label("Delay");
	
	scl_time_.set_value(0.2);
	scl_time_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_delay::timechg));
	
	box_time_.pack_start(lbl_time_, false, false, 5);
	box_time_.pack_start(scl_time_, true, true, 5);
	
	gauche_.pack_start(box_time_, false, false, 5);
	
	scl_feedback_.set_value(0.5);
	scl_time_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_delay::fbchg));
	
	box_feedback_.pack_start(lbl_feedback_, false, false, 5);
	box_feedback_.pack_start(scl_feedback_, true, true, 5);
	
	gauche_.pack_start(box_feedback_, false, false, 5);
}

void tranche_delay::timechg() {
	if(e_ != 0)
		static_cast<delay*>(e_)->time(scl_time_.get_value());
}

void tranche_delay::fbchg() {
	if(e_ != 0)
		static_cast<delay*>(e_)->feedback(scl_feedback_.get_value());
}