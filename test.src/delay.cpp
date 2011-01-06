#include "delay.h"

void delay::operator()() {
		// Pas d'allongement, baby
		//size_t ancienne_fin = echantillon_fin();
		allonger();
		// Disto !
		size_t echantillon_delay = static_cast<size_t>(time_ * in().rate());
		for(size_t i=echantillon_debut()+echantillon_delay; i<echantillon_fin(); ++i) {
			out().data()[i] = out().data()[i] + out().data()[i-echantillon_delay] * feedback_;

		}
}