#if !defined(TRANCHE_HIGHPASS_H_NW9N7M0T)
#define TRANCHE_HIGHPASS_H_NW9N7M0T

#include "tranche_effet.h"

struct tranche_highpass : public tranche_effet {
	tranche_highpass(controleur&, effet*, int);
	~tranche_highpass() {}
	
	void freq();
private:
	Gtk::HBox box_freq_;
	Gtk::Label lbl_freq_;
	Gtk::HScale scl_freq_;
};

#endif /* end of include guard: TRANCHE_HIGHPASS_H_NW9N7M0T */
