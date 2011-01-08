#include "volume.h"
#include <son.h>

void volume::operator()() {
		// Volioume
	for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i) {
		out().data()[i] = std::max(-1.0, std::min(1.0, in().data()[i] * gain_));
	}
		
	mixer_drywet();
}