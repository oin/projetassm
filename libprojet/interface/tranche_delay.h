#if !defined(TRANCHE_DELAY_H_6RGWYU2C)
#define TRANCHE_DELAY_H_6RGWYU2C

#include "tranche_effet.h"

struct tranche_delay : public tranche_effet {
	tranche_delay(controleur&, effet*, int);
	~tranche_delay() {}
	
	void timechg();
	void fbchg();
private:
	Gtk::HBox box_time_;
	Gtk::Label lbl_time_;
	Gtk::HScale scl_time_;
	Gtk::HBox box_feedback_;
	Gtk::Label lbl_feedback_;
	Gtk::HScale scl_feedback_;
};

#endif /* end of include guard: TRANCHE_DELAY_H_6RGWYU2C */
