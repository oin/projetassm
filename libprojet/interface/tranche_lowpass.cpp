#include "tranche_lowpass.h"
#include "controleur.h"
#include <lowpass.h>

tranche_lowpass::tranche_lowpass(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet), lbl_freq_("Fréquence (Hz) :"), scl_freq_(0.0, 44100.0, 1.0) {
	conteneur_.set_label("Passe-bas");
	
	scl_freq_.set_value(100.0);
	scl_freq_.signal_value_changed().connect(sigc::mem_fun(*this, &tranche_lowpass::freq));
	
	box_freq_.pack_start(lbl_freq_, false, false, 5);
	box_freq_.pack_start(scl_freq_, true, true, 5);
	
	gauche_.pack_start(box_freq_, false, false, 5);
}

void tranche_lowpass::freq() {
	if(e_ != 0)
		static_cast<lowpass*>(e_)->freq(scl_freq_.get_value());
}