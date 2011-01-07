#include "inverse.h"

void inverse::operator()() {
	for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i)
		out().data()[echantillon_fin()-i] = in().data()[i];
}