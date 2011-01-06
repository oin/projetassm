#include "distorsion.h"

void distorsion::operator()() {
		// Pas d'allongement, baby
		// allonger();
		// Disto !
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i) {
			out().data()[i] =
				// On mixe le signal distordu
				std::min(1.0, std::max(-1.0, in().data()[i] * gain_)) * wet() 
				+
				// Et le signal d'origine
				in().data()[i] * dry();
		}
}