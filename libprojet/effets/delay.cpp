#include "delay.h"
#include <son.h>

void delay::operator()() {
	// Delay lay lay lay !
	size_t echantillon_delay = static_cast<size_t>(time_ * in().rate());
	
	assm::son tmp(out().size(), out().rate());
	
	for(size_t i=echantillon_debut(); i + echantillon_delay < echantillon_fin(); ++i) {
		tmp.data()[i + echantillon_delay] = in().data()[i] + tmp.data()[i] * feedback_;
	}
	
	// Copie tmp dans le son à l'emplacement qu'il faut
	std::copy(tmp.begin() + echantillon_debut(), tmp.begin()  + echantillon_fin(), out().begin() + echantillon_debut());
	
	// Mixe
	mixer_drywet();
}