#include "noise_gate.h"
#include <son.h>

void noise_gate::operator()() {
		// Noise gate !
		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i){
		  if(in().data()[i] < limit_){
			out().data()[i] = 0.0;
		  }
		}
}