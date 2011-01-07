#include "inverse.h"

void inverse::operator()() {
		// Pas d'allongement, baby
		// allonger();
		// Disto !
				
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i)
				out().data()[echantillon_fin()-i] = in().data()[i];
}