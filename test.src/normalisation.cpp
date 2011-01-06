#include "normalisation.h"

void normalisation::operator()() {
		// Pas d'allongement, baby
		// allonger();
		// Disto !
		double max = *std::max_element(in().data().begin()+echantillon_debut(),in().data().begin()+echantillon_fin());
				
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i)
				out().data()[i] = in().data()[i]/max;
}