#if !defined(TRANCHE_VOLUME_H_WIWKFKJM)
#define TRANCHE_VOLUME_H_WIWKFKJM

#include "tranche_effet.h"

struct tranche_volume : public tranche_effet {
	tranche_volume(controleur&, effet*, int);
	~tranche_volume() {}
	
	void gainchg();
private:
	Gtk::HBox box_gain_;
	Gtk::Label lbl_gain_;
	Gtk::HScale scl_gain_;
};

#endif /* end of include guard: TRANCHE_VOLUME_H_WIWKFKJM */
