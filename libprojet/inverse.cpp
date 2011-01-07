#include "inverse.h"

void inverse::operator()() {
	for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i)
		out().data()[echantillon_fin() - (i - echantillon_debut())] = in().data()[i];
	
	mixer_drywet();
}