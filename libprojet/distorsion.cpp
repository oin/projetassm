#include "distorsion.h"

void distorsion::operator()() {
		// Disto !
	for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i) {
		out().data()[i] = std::max(-1.0, std::min(1.0, in().data()[i] * gain_)) / gain_;
	}
		
	mixer_drywet();
}