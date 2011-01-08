#if !defined(TRANCHE_LOWPASS_H_AX43NMD1)
#define TRANCHE_LOWPASS_H_AX43NMD1

#include "tranche_effet.h"

struct tranche_lowpass : public tranche_effet {
	tranche_lowpass(controleur&, effet*, int);
	~tranche_lowpass() {}
	
	void freq();
private:
	Gtk::HBox box_freq_;
	Gtk::Label lbl_freq_;
	Gtk::HScale scl_freq_;
};

#endif /* end of include guard: TRANCHE_LOWPASS_H_AX43NMD1 */
