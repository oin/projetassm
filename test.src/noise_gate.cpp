#include "noise_gate.h"
#include <iostream>

void noise_gate::operator()() {
		// Pas d'allongement, baby
		// allonger();
		// Disto !
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i){
		  if(in().data()[i] < limit_){
			out().data()[i] = 0.0;
		  }
		}
}